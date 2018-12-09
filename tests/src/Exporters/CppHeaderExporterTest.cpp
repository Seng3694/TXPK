#include <catch2/catch.hpp>

#include <json.hpp>
#include <fstream>

#include <TXPK/KeyConverters/EnumeratorConverter.hpp>
#include <TXPK/Exporters/CppHeaderExporter.hpp>

TEST_CASE("CppHeader Export", "[TXPK/Exporters/CppHeaderExporter]")
{
	using namespace txpk;

	//simulate loading real textures
	Color4 raw[] =
	{
		{ 0,0,0,0 },{ 0,0,0,0 },
		{ 0,0,0,0 },{ 0,0,0,0 }
	};
	Texture texture;
	texture.loadFromMemory(raw, 2, 2);
	texture.save("texture_1.png");
	texture.save("texture_2.png");

	TexturePtr texture1 = std::make_shared<Texture>();
	texture1->loadFromFile("texture_1.png");
	TexturePtr texture2 = std::make_shared<Texture>();
	texture2->loadFromFile("texture_2.png");
	texture2->getBounds()->left = 2;

	//we can actually delete these textures now
	std::remove("texture_1.png");
	std::remove("texture_2.png");

	TexturePtrs textures;
	textures.push_back(texture1);
	textures.push_back(texture2);

	//use a converter which converts key to an integer, because the exporter works best with integer values
	ServiceLocator::current()->registerInstance<IKeyConverter>(std::make_shared<EnumeratorConverter>());

	DataExporterPtr cppHeaderExporter = std::make_shared<CppHeaderExporter>();
	//we are just assuming these so textures got packed right next to each other building a 4x2 texture
	cppHeaderExporter->exportData(textures, 4, 2, "not/relevant.png", "", "header");
	//this should have created a "header.hpp" file in the current directory
	//wich should look like this:
	//#pragma once
	//
	//#define TEXTURE_1 0
	//#define TEXTURE_2 1
	//

	std::ifstream stream("header.hpp");

	std::string contents;
	std::string expected = 
		"#pragma once\n\n"
		"#define TEXTURE_1 0\n"
		"#define TEXTURE_2 1\n";

	if (stream.is_open())
	{
		contents = std::string(
			std::istreambuf_iterator<char>(stream),
			std::istreambuf_iterator<char>());

		stream.close();
		std::remove("header.hpp");
	}

	REQUIRE(contents == expected);
}
