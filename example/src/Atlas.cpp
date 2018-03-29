#include "Atlas.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool Atlas::load(const std::string &p)
{
	std::ifstream stream(p);

	if (stream.is_open())
	{
		nlohmann::json data;
		stream >> data;

		path = data.at("path").get<std::string>();
		
		for (auto &t : data.at("bin").get<std::vector<nlohmann::json>>())
		{
			auto texture = Texture();
			texture.x = t.at("x").get<int>();
			texture.y = t.at("y").get<int>();
			texture.w = t.at("w").get<int>();
			texture.h = t.at("h").get<int>();
			texture.flip = t.at("flip").get<int>();
			texture.path = t.at("path").get<std::string>();
			textures.push_back(texture);
		}

		stream.close();

		return texture.loadFromFile(path);
	}
	else
	{
		return false;
	}
}