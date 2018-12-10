#include <catch2/catch.hpp>

#include <fstream>

#include <TXPK/Exporters/JsonExporter.hpp>
#include <TXPK/Exporters/CppHeaderExporter.hpp>
#include <TXPK/Exporters/MultiExporter.hpp>

TEST_CASE("Multi Export", "[TXPK/Exporters/MultiExporter]")
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
	ServiceLocator::current()->registerInstance<IKeyConverter>(std::make_shared<EnumeratorConverter>());

	std::shared_ptr<MultiExporter> multiExporter = std::make_shared<MultiExporter>();
	multiExporter->addExporter(std::make_shared<JsonExporter>());
	multiExporter->addExporter(std::make_shared<CppHeaderExporter>());

	//we are just assuming these so textures got packed right next to each other building a 4x2 texture
	multiExporter->exportData(textures, 4, 2, "not/relevant.png", "", "test");
	//this should have created a "test.json" file and a "test.hpp" in the current directory

	std::ifstream stream("test.json");
	REQUIRE(stream.is_open());
	stream.close();
	std::remove("test.json");

	stream.open("test.hpp");
	REQUIRE(stream.is_open());
	stream.close();
	std::remove("test.hpp");
}
