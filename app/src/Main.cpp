#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <experimental/filesystem>
#include <regex>

#include <SFML/Graphics.hpp>

#include "TextureInfo.h"
#include "JsonConverter.h"
#include "Packer.h"
#include "ImageRenderer.h"

namespace fs = std::experimental::filesystem;

std::vector<std::string> getFileNamesInDirectory(const std::string &directory, const std::string &fileRegex)
{
	std::vector<std::string> files;
	auto fileNameRegex = std::regex("[a-zA-Z0-9-_\\{\\}\\(\\)\\[\\]\\.]+$"); //escaping regex escapes...
	auto userRegex = std::regex(fileRegex);
	
	for (auto &itr : fs::directory_iterator(directory))
	{
		const auto path = itr.path().string();
		std::smatch match;

		if (std::regex_search(path.begin(), path.end(), match, fileNameRegex))
		{
			const std::string fileName = match[0];
			if (std::regex_search(fileName.begin(), fileName.end(), match, userRegex))
				files.push_back(fileName);
		}
	}

	return files;
}

int main(int argc, const char** argv)
{
	if (argc < 2) return 0;

	std::string fileRegex = "";
	std::string folderPath = "";
	std::string outputName = "atlas";
	auto allowFlip = false;
	auto clearColor = sf::Color::Transparent;

	try
	{
		if (argc > 1) folderPath = argv[1];
		if (argc > 2) outputName = argv[2];
		if (argc > 3) allowFlip = std::stoi(argv[3]) > 0 ? 1 : 0;
		if (argc > 4) fileRegex = argv[4];
		if (argc > 5)
		{
			unsigned int packed;
			std::stringstream ss;
			ss << std::hex << argv[5];
			ss >> packed;
			clearColor = sf::Color(packed);
		}
	}
	catch (std::string &exception)
	{
		std::cout << "invalid arguments" << std::endl << exception << std::endl;
		system("pause");
		return 0;
	}

	std::replace(folderPath.begin(), folderPath.end(), '\\', '/');
	auto textures = std::unordered_map<std::string, sf::Texture>();
	auto textureInfos = std::vector<TextureInfo>();

	for (auto &file : getFileNamesInDirectory(folderPath, fileRegex))
	{
		auto texture = sf::Texture();
		if (texture.loadFromFile(folderPath + "/" + file))
		{
			auto info = TextureInfo{ Rectangle(texture.getSize().x, texture.getSize().y), file };
			textures.emplace(file, texture);
			textureInfos.push_back(info);
		}

	}

	auto bin = Packer::pack(textureInfos, allowFlip);
	JsonConverter::saveToJson(folderPath, outputName, bin);

	auto image = ImageRenderer::draw(bin, textures, clearColor);
	image.saveToFile(std::string(folderPath) + "/" + outputName + ".png");

	return 0;
}