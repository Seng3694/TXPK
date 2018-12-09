#include <catch2/catch.hpp>

#include <TXPK/Core/Bin.hpp>

TEST_CASE("Bin can be constructed", "[TXPK/Core/Bin]")
{
	using namespace txpk;

	RectanglePtrs rectangles;
	rectangles.push_back(std::make_shared<txpk::Rectangle>(txpk::Rectangle(3, 4)));
	//rectangles.push_back(new txpk::Rectangle(3, 4));

	txpk::Bin bin(rectangles);

	SECTION("Rectangle has the size constructed with")
	{
		REQUIRE(bin.rectangles.size() == 1);
		REQUIRE(bin.rectangles[0]->left == 0);
		REQUIRE(bin.rectangles[0]->top == 0);
		REQUIRE(bin.rectangles[0]->width == 3);
		REQUIRE(bin.rectangles[0]->height == 4);
	}

	SECTION("When changing rectangles in Bin, they are changing in source too")
	{
		REQUIRE(rectangles[0]->width == 3);
		REQUIRE(rectangles[0]->height == 4);
		bin.rectangles[0]->rotate();
		REQUIRE(bin.rectangles[0]->width == 4);
		REQUIRE(bin.rectangles[0]->height == 3);
		REQUIRE(rectangles[0]->width == 4);
		REQUIRE(rectangles[0]->height == 3);
	}
}

TEST_CASE("Bin can be saved", "[TXPK/Core/Bin]")
{
	using namespace txpk;

	Color4 aPixelData[]
	{
		{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 },
		{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 },
		{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,0 }
	};

	Color4 bPixelData[]
	{
		{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,0 },
		{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 },
		{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 }
	};

	TexturePtr aTexture = std::make_shared<txpk::Texture>();
	REQUIRE(aTexture->loadFromMemory(aPixelData, 4, 3));
	TexturePtr bTexture = std::make_shared<txpk::Texture>();;
	REQUIRE(bTexture->loadFromMemory(bPixelData, 4, 3));

	//because we don't want to use any packers here, we just move the rectangle of b manually
	bTexture->getBounds()->left = 4;

	TexturePtrs textures;
	textures.push_back(aTexture);
	textures.push_back(bTexture);

	RectanglePtrs rectangles;
	rectangles.push_back(aTexture->getBounds());
	rectangles.push_back(bTexture->getBounds());

	/*
	It will be assumed that the images a and b are aligned like that:

	aaaabbbb
	aaaabbbb
	aaaabbbb

	*/

	Bin bin(rectangles);
	//and because there is no packing involved, the bin size was never set
	bin.width = 8;
	bin.height = 3;

	SECTION("with a transparent clear color and without trimming")
	{
		Color4 clearColor = { 0,0,0,0 };

		//there will be an actual images saved
		REQUIRE(bin.save(textures, clearColor, "testpath.png", false));

		TexturePtr binTexture = std::make_shared<txpk::Texture>();
		REQUIRE(binTexture->loadFromFile("testpath.png"));

		Color4 expectedPixelData[]
		{
			{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 },{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,0 },
			{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 },{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 },
			{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,0 },{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 }
		};
		TexturePtr expectedTexture = std::make_shared<txpk::Texture>();
		REQUIRE(expectedTexture->loadFromMemory(expectedPixelData, 8, 3));

		REQUIRE(*binTexture == *expectedTexture);
	}

	SECTION("with a red clear color and without trimming")
	{
		Color4 clearColor = { 255,0,0,255 };

		//there will be an actual images saved
		REQUIRE(bin.save(textures, clearColor, "testpath.png", false));

		TexturePtr binTexture = std::make_shared<txpk::Texture>();
		REQUIRE(binTexture->loadFromFile("testpath.png"));

		//so with a red color, every transparent pixel should be read instead
		Color4 expectedPixelData[]
		{
			{ 0,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 0,0,0,255 },{   0,0,0,255 },{   0,0,0,255 },{ 255,0,0,255 },
			{ 0,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 0,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },
			{ 0,0,0,255 },{   0,0,0,255 },{   0,0,0,255 },{ 255,0,0,255 },{ 0,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 }
		};
		TexturePtr expectedTexture = std::make_shared<txpk::Texture>();
		REQUIRE(expectedTexture->loadFromMemory(expectedPixelData, 8, 3));

		REQUIRE(*binTexture == *expectedTexture);
	}

	SECTION("with a transparent clear color and with trimming")
	{
		Color4 clearColor = { 0,0,0,0 };

		//there will be an actual images saved
		REQUIRE(bin.save(textures, clearColor, "testpath.png", true));

		TexturePtr binTexture = std::make_shared<txpk::Texture>();
		REQUIRE(binTexture->loadFromFile("testpath.png"));

		//the trimming refers to trimming the result image not the subtextures. That is work done before packing
		//notice how the pixel data is just 7x3 because the right most column got trimmed
		Color4 expectedPixelData[]
		{
			{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 },{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,255 },
			{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },{ 0,0,0,0 },{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 },
			{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,255 },{ 0,0,0,0 },{ 0,0,0,255 },{ 0,0,0,  0 },{ 0,0,0,  0 }
		};
		TexturePtr expectedTexture = std::make_shared<txpk::Texture>();
		REQUIRE(expectedTexture->loadFromMemory(expectedPixelData, 7, 3));

		REQUIRE(*binTexture == *expectedTexture);
	}

	SECTION("with a red clear color and with trimming")
	{
		Color4 clearColor = { 255,0,0,255 };

		//there will be an actual images saved
		REQUIRE(bin.save(textures, clearColor, "testpath.png", true));

		TexturePtr binTexture = std::make_shared<txpk::Texture>();
		REQUIRE(binTexture->loadFromFile("testpath.png"));

		//because of the red clear color, there is no transparency to cut away. So it should be 8x3 like the one without trimming
		Color4 expectedPixelData[]
		{
			{ 0,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 0,0,0,255 },{   0,0,0,255 },{   0,0,0,255 },{ 255,0,0,255 },
			{ 0,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 0,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },
			{ 0,0,0,255 },{   0,0,0,255 },{   0,0,0,255 },{ 255,0,0,255 },{ 0,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 },{ 255,0,0,255 }
		};
		TexturePtr expectedTexture = std::make_shared<txpk::Texture>();
		REQUIRE(expectedTexture->loadFromMemory(expectedPixelData, 8, 3));

		REQUIRE(*binTexture == *expectedTexture);
	}

	//cleanup the created image
	std::remove("testpath.png");
}