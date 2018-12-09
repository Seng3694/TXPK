#include <catch2/catch.hpp>

#include <TXPK/Core/RectangleMerger.hpp>

TEST_CASE("Rectangles can be merged", "[TXPK/Core/RectangleMerger]")
{
	using namespace txpk;

	SECTION("The same texture")
	{
		Color4 raw[] = 
		{
			{ 255, 0, 0, 255 }
		};

		TexturePtr a = std::make_shared<txpk::Texture>();
		REQUIRE(a->loadFromMemory(raw, 1, 1));
		TexturePtr b = std::make_shared<txpk::Texture>();
		REQUIRE(b->loadFromMemory(raw, 1, 1));

		//both underlying rectangles should have different memory addresses
		REQUIRE(&(*a->getBounds()) != &(*b->getBounds()));

		TexturePtrs textures;
		textures.push_back(a);
		textures.push_back(b);

		RectanglePtrs rectangles = txpk::merge_rectangles(textures);

		REQUIRE(rectangles.size() == 1);
		REQUIRE(rectangles[0]->width == 1);
		REQUIRE(rectangles[0]->height == 1);
		
		//now they should point to the same rectangle
		REQUIRE(&(*a->getBounds()) == &(*b->getBounds()));
		REQUIRE(&(*rectangles[0]) == &(*a->getBounds()));
		REQUIRE(&(*rectangles[0]) == &(*b->getBounds()));

		rectangles[0]->left = 1000;
	}

	SECTION("Different texture")
	{
		Color4 raw1[] =
		{
			{ 255, 0, 0, 255 }
		};

		Color4 raw2[] =
		{
			{ 0, 255, 0, 255 }
		};

		TexturePtr a = std::make_shared<txpk::Texture>();
		REQUIRE(a->loadFromMemory(raw1, 1, 1));
		TexturePtr b = std::make_shared<txpk::Texture>();
		REQUIRE(b->loadFromMemory(raw2, 1, 1));

		//both underlying rectangles should have different memory addresses
		REQUIRE(&(*a->getBounds()) != &(*b->getBounds()));

		TexturePtrs textures;
		textures.push_back(a);
		textures.push_back(b);

		RectanglePtrs rectangles = txpk::merge_rectangles(textures);

		REQUIRE(rectangles.size() == 2);

		REQUIRE(&(*a->getBounds()) != &(*b->getBounds()));
		REQUIRE(&(*rectangles[0]) == &(*a->getBounds()));
		REQUIRE(&(*rectangles[1]) == &(*b->getBounds()));
	}

	SECTION("Mixed textures")
	{
		Color4 raw1[] =
		{
			{ 255, 0, 0, 255 }
		};

		Color4 raw2[] =
		{
			{ 0, 255, 0, 255 }
		};

		TexturePtr a = std::make_shared<txpk::Texture>();
		REQUIRE(a->loadFromMemory(raw1, 1, 1));
		TexturePtr b = std::make_shared<txpk::Texture>();
		REQUIRE(b->loadFromMemory(raw2, 1, 1));
		TexturePtr c = std::make_shared<txpk::Texture>();
		REQUIRE(c->loadFromMemory(raw2, 1, 1));

		TexturePtrs textures;
		textures.push_back(a);
		textures.push_back(b);
		textures.push_back(c);

		RectanglePtrs rectangles = txpk::merge_rectangles(textures);

		REQUIRE(rectangles.size() == 2);

		REQUIRE(&(*a->getBounds()) != &(*b->getBounds()));
		REQUIRE(&(*b->getBounds()) == &(*c->getBounds()));
		REQUIRE(&(*rectangles[0]) == &(*a->getBounds()));
		REQUIRE(&(*rectangles[1]) == &(*b->getBounds()));
		REQUIRE(&(*rectangles[1]) == &(*c->getBounds()));
	}
}