#include <catch2/catch.hpp>

#include <fstream>

#include <TXPK/KeyConverters/FileWithoutExtConverter.hpp>
#include <TXPK/Exporters/LuaExporter.hpp>

TEST_CASE("Lua Export", "[TXPK/Exporters/LuaExporter]")
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
	ServiceLocator::current()->clear();
	ServiceLocator::current()->registerInstance<IKeyConverter>(std::make_shared<FileWithoutExtConverter>());

	//this lua file should create a .txt file with img="path/to/image.png",w="123",h="123" etc
	DataExporterPtr luaExporter = std::make_shared<LuaExporter>(LuaExporter("content/TxtExporter.lua"));
	//we are just assuming these so textures got packed right next to each other building a 4x2 texture
	luaExporter->exportData(textures, 4, 2, "not/relevant.png", "", "file");
	//this should have created a "file.txt" file in the current directory

	std::string expected =
		"img=\"not/relevant.png\",w=\"4\",h=\"2\"\n"
		"key=\"texture_1\",x=\"0\",y=\"0\",w=\"2\",h=\"2\",ox=\"0\",oy=\"0\",sw=\"2\",sh=\"2\",r=\"false\"\n"
		"key=\"texture_2\",x=\"2\",y=\"0\",w=\"2\",h=\"2\",ox=\"0\",oy=\"0\",sw=\"2\",sh=\"2\",r=\"false\"\n";

	std::string contents;

	std::ifstream stream("file.txt");
	REQUIRE(stream.is_open());

	contents = std::string(
		std::istreambuf_iterator<char>(stream),
		std::istreambuf_iterator<char>());

	stream.close();
	std::remove("file.txt");

	REQUIRE(contents == expected);
}
