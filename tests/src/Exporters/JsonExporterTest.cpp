#include <catch2/catch.hpp>

#include <json.hpp>
#include <fstream>

#include <TXPK/Exporters/JsonExporter.hpp>

TEST_CASE("Json Export", "[TXPK/Exporters/JsonExporter]")
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
	texture.save("texture1.png");
	texture.save("texture2.png");
	
	TexturePtr texture1 = std::make_shared<Texture>();
	texture1->loadFromFile("texture1.png");
	TexturePtr texture2 = std::make_shared<Texture>();
	texture2->loadFromFile("texture2.png");
	texture2->getBounds()->left = 2;

	//we can actually delete these textures now
	std::remove("texture1.png");
	std::remove("texture2.png");

	TexturePtrs textures;
	textures.push_back(texture1);
	textures.push_back(texture2);
	
	//because there could be a KeyConverter registered
	ServiceLocator::current()->clear();

	DataExporterPtr jsonExporter = std::make_shared<JsonExporter>();
	//we are just assuming these so textures got packed right next to each other building a 4x2 texture
	jsonExporter->exportData(textures, 4, 2, "not/relevant.png", "", "jsontest");
	//this should have created a "jsontest.json" file in the current directory

	std::ifstream stream("jsontest.json");
	if (stream.is_open())
	{
		nlohmann::json json;
		REQUIRE_NOTHROW(stream >> json);

		REQUIRE(json.at("meta").at("w").get<int32>() == 4);
		REQUIRE(json.at("meta").at("h").get<int32>() == 2);
		REQUIRE(json.at("meta").at("img").get<std::string>() == "not/relevant.png");

		REQUIRE(json.at("bin").size() == 2);
		auto item1 = json.at("bin")[0];
		auto item2 = json.at("bin")[1];

		REQUIRE(item1.at("key").get<std::string>() == "texture1.png");
		REQUIRE(item1.at("x").get<int32>() == 0);
		REQUIRE(item1.at("y").get<int32>() == 0);
		REQUIRE(item1.at("w").get<int32>() == 2);
		REQUIRE(item1.at("h").get<int32>() == 2);
		REQUIRE(item1.at("ox").get<int32>() == 0);
		REQUIRE(item1.at("oy").get<int32>() == 0);
		REQUIRE(item1.at("sw").get<int32>() == 2);
		REQUIRE(item1.at("sh").get<int32>() == 2);
		REQUIRE(item1.at("r").get<bool>() == false);

		REQUIRE(item2.at("key").get<std::string>() == "texture2.png");
		REQUIRE(item2.at("x").get<int32>() == 2);
		REQUIRE(item2.at("y").get<int32>() == 0);
		REQUIRE(item2.at("w").get<int32>() == 2);
		REQUIRE(item2.at("h").get<int32>() == 2);
		REQUIRE(item2.at("ox").get<int32>() == 0);
		REQUIRE(item2.at("oy").get<int32>() == 0);
		REQUIRE(item2.at("sw").get<int32>() == 2);
		REQUIRE(item2.at("sh").get<int32>() == 2);
		REQUIRE(item2.at("r").get<bool>() == false);
		
		stream.close();
	}

	std::remove("jsontest.json");
}
