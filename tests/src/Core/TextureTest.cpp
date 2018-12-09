#include <catch2/catch.hpp>

#include <TXPK/Core/Texture.hpp>

TEST_CASE("Texture can be created", "[TXPK/Core/Texture]")
{
	using namespace txpk;

	Texture texture1;
	REQUIRE(texture1.getPath() == "");
	REQUIRE((texture1.getBounds() == NULL));
	REQUIRE(texture1.getOffsetX() == 0);
	REQUIRE(texture1.getOffsetY() == 0);
	REQUIRE(texture1.getSourceWidth() == 0);
	REQUIRE(texture1.getSourceHeight() == 0);
	REQUIRE(texture1.getRawPixelData().empty());

	texture1.setOffsetX(10);
	texture1.setOffsetY(20);
	texture1.setBounds(std::make_shared<txpk::Rectangle>(txpk::Rectangle(10, 20)));
	REQUIRE(texture1.getOffsetX() == 10);
	REQUIRE(texture1.getOffsetY() == 20);
	REQUIRE((texture1.getBounds() != NULL));
	REQUIRE(texture1.getBounds()->width == 10);
	REQUIRE(texture1.getBounds()->height == 20);

	//copy ctor
	Texture texture2 = texture1;
	texture2.setOffsetX(30);
	REQUIRE(texture2.getOffsetX() != texture1.getOffsetX());
	//should both reference the same rectangle
	REQUIRE(&(*texture2.getBounds()) == &(*texture1.getBounds()));
}

TEST_CASE("Texture can be loaded from memory", "[TXPK/Core/Texture]")
{
	using namespace txpk;

	Color4 raw[] =
	{
		{ 255,0,  0,255 },{   0,255,  0,255 },
		{   0,0,255,255 },{ 255,  0,255,255 }
	};

	Texture texture;
	REQUIRE(texture.loadFromMemory(raw, 2, 2));
	REQUIRE(texture.getPath() == "");
	REQUIRE((texture.getBounds() != NULL));
	REQUIRE(texture.getBounds()->width == 2);
	REQUIRE(texture.getBounds()->height == 2);
	REQUIRE(texture.getOffsetX() == 0);
	REQUIRE(texture.getOffsetY() == 0);
	REQUIRE(texture.getSourceWidth() == 2);
	REQUIRE(texture.getSourceHeight() == 2);
	REQUIRE(!texture.getRawPixelData().empty());
	REQUIRE(array_equals(&texture.getRawPixelData()[0], raw, 4));
}

TEST_CASE("Texture can be saved", "[TXPK/Core/Texture]")
{
	using namespace txpk;

	Color4 raw[] =
	{
		{ 255,0,  0,255 },{   0,255,  0,255 },
		{   0,0,255,255 },{ 255,  0,255,255 }
	};

	Texture texture;
	REQUIRE(texture.loadFromMemory(raw, 2, 2));

	SECTION("as png")
	{
		REQUIRE(texture.save("test.png"));
		std::remove("test.png");
	}

	SECTION("as jpg")
	{
		REQUIRE(texture.save("test.jpg"));
		std::remove("test.jpg");
	}

	SECTION("as jpeg")
	{
		REQUIRE(texture.save("test.jpeg"));
		std::remove("test.jpeg");
	}

	SECTION("not as bmp")
	{
		REQUIRE(!texture.save("test.bmp"));
	}
}

TEST_CASE("Texture can be loaded from a file", "[TXPK/Core/Texture]")
{
	using namespace txpk;

	Color4 raw[] =
	{
		{ 255,0,  0,255 },{   0,255,  0,255 },
		{   0,0,255,255 },{ 255,  0,255,255 }
	};

	Texture texture;
	REQUIRE(texture.loadFromMemory(raw, 2, 2));

	SECTION("from png")
	{
		REQUIRE(texture.save("test.png"));

		Texture loadedTexture;
		REQUIRE(loadedTexture.loadFromFile("test.png"));
		REQUIRE(loadedTexture.getPath() == "test.png");
		REQUIRE((loadedTexture.getBounds() != NULL));
		REQUIRE(loadedTexture.getBounds()->width == 2);
		REQUIRE(loadedTexture.getBounds()->height == 2);
		REQUIRE(loadedTexture.getOffsetX() == 0);
		REQUIRE(loadedTexture.getOffsetY() == 0);
		REQUIRE(loadedTexture.getSourceWidth() == 2);
		REQUIRE(loadedTexture.getSourceHeight() == 2);
		REQUIRE(!loadedTexture.getRawPixelData().empty());
		REQUIRE(array_equals(&loadedTexture.getRawPixelData()[0], raw, 4));

		std::remove("test.png");
	}

	SECTION("from jpg")
	{
		REQUIRE(texture.save("test.jpg"));

		Texture loadedTexture;
		REQUIRE(loadedTexture.loadFromFile("test.jpg"));
		REQUIRE(loadedTexture.getPath() == "test.jpg");
		REQUIRE((loadedTexture.getBounds() != NULL));
		REQUIRE(loadedTexture.getBounds()->width == 2);
		REQUIRE(loadedTexture.getBounds()->height == 2);
		REQUIRE(loadedTexture.getOffsetX() == 0);
		REQUIRE(loadedTexture.getOffsetY() == 0);
		REQUIRE(loadedTexture.getSourceWidth() == 2);
		REQUIRE(loadedTexture.getSourceHeight() == 2);
		REQUIRE(!loadedTexture.getRawPixelData().empty());
		
		//because jpg is not accurate we have to accept some error range
		int32 error = 2;
		auto pixels = loadedTexture.getRawPixelData();
		for (uint32 i = 0; i < pixels.size(); ++i)
		{
			REQUIRE(abs(pixels[i].data[0] - raw[i].data[0]) <= error);
			REQUIRE(abs(pixels[i].data[1] - raw[i].data[1]) <= error);
			REQUIRE(abs(pixels[i].data[2] - raw[i].data[2]) <= error);
			REQUIRE(abs(pixels[i].data[3] - raw[i].data[3]) <= error);
		}

		std::remove("test.jpg");
	}

	SECTION("from jpeg")
	{
		REQUIRE(texture.save("test.jpeg"));

		Texture loadedTexture;
		REQUIRE(loadedTexture.loadFromFile("test.jpeg"));
		REQUIRE(loadedTexture.getPath() == "test.jpeg");
		REQUIRE((loadedTexture.getBounds() != NULL));
		REQUIRE(loadedTexture.getBounds()->width == 2);
		REQUIRE(loadedTexture.getBounds()->height == 2);
		REQUIRE(loadedTexture.getOffsetX() == 0);
		REQUIRE(loadedTexture.getOffsetY() == 0);
		REQUIRE(loadedTexture.getSourceWidth() == 2);
		REQUIRE(loadedTexture.getSourceHeight() == 2);
		REQUIRE(!loadedTexture.getRawPixelData().empty());

		//because jpeg is not accurate we have to accept some error range
		int32 error = 2;
		auto pixels = loadedTexture.getRawPixelData();
		for (uint32 i = 0; i < pixels.size(); ++i)
		{
			REQUIRE(abs(pixels[i].data[0] - raw[i].data[0]) <= error);
			REQUIRE(abs(pixels[i].data[1] - raw[i].data[1]) <= error);
			REQUIRE(abs(pixels[i].data[2] - raw[i].data[2]) <= error);
			REQUIRE(abs(pixels[i].data[3] - raw[i].data[3]) <= error);
		}

		std::remove("test.jpeg");
	}
}

TEST_CASE("Texture can be trimmed", "[TXPK/Core/Texture]")
{
	using namespace txpk;

	SECTION("When there is nothing to trim")
	{
		Color4 raw[] =
		{
			{ 255,0,  0,255 },{   0,255,  0,255 },
			{   0,0,255,255 },{ 255,  0,255,255 }
		};

		Texture texture;
		REQUIRE(texture.loadFromMemory(raw, 2, 2));
		texture.trim();
		REQUIRE(texture.getBounds()->width == 2);
		REQUIRE(texture.getBounds()->height == 2);
		REQUIRE(texture.getOffsetX() == 0);
		REQUIRE(texture.getOffsetY() == 0);
		REQUIRE(texture.getSourceWidth() == 2);
		REQUIRE(texture.getSourceHeight() == 2);
	}
	
	SECTION("Left side")
	{
		Color4 raw[] =
		{
			{ 0,0,0,0 },{ 255,0,  0,255 },{   0,255,  0,255 },
			{ 0,0,0,0 },{   0,0,255,255 },{ 255,  0,255,255 }
		};

		Texture texture;
		REQUIRE(texture.loadFromMemory(raw, 3, 2));
		texture.trim();
		REQUIRE(texture.getBounds()->width == 2);
		REQUIRE(texture.getBounds()->height == 2);
		REQUIRE(texture.getOffsetX() == 1);
		REQUIRE(texture.getOffsetY() == 0);
		REQUIRE(texture.getSourceWidth() == 3);
		REQUIRE(texture.getSourceHeight() == 2);
	}
	
	SECTION("Top side")
	{
		Color4 raw[] =
		{
			{   0,0,  0,  0 },{   0,  0,  0,  0 },
			{ 255,0,  0,255 },{   0,255,  0,255 },
			{   0,0,255,255 },{ 255,  0,255,255 }
		};

		Texture texture;
		REQUIRE(texture.loadFromMemory(raw, 2, 3));
		texture.trim();
		REQUIRE(texture.getBounds()->width == 2);
		REQUIRE(texture.getBounds()->height == 2);
		REQUIRE(texture.getOffsetX() == 0);
		REQUIRE(texture.getOffsetY() == 1);
		REQUIRE(texture.getSourceWidth() == 2);
		REQUIRE(texture.getSourceHeight() == 3);
	}

	SECTION("Right side")
	{
		Color4 raw[] =
		{
			{ 255,0,  0,255 },{   0,255,  0,255 },{ 0,0,0,0 },
			{   0,0,255,255 },{ 255,  0,255,255 },{ 0,0,0,0 }
		};

		Texture texture;
		REQUIRE(texture.loadFromMemory(raw, 3, 2));
		texture.trim();
		REQUIRE(texture.getBounds()->width == 2);
		REQUIRE(texture.getBounds()->height == 2);
		REQUIRE(texture.getOffsetX() == 0);
		REQUIRE(texture.getOffsetY() == 0);
		REQUIRE(texture.getSourceWidth() == 3);
		REQUIRE(texture.getSourceHeight() == 2);
	}
	
	SECTION("Bottom side")
	{
		Color4 raw[] =
		{
			{ 255,0,  0,255 },{   0,255,  0,255 },
			{   0,0,255,255 },{ 255,  0,255,255 },
			{   0,0,  0,  0 },{   0,  0,  0,  0 }
		};

		Texture texture;
		REQUIRE(texture.loadFromMemory(raw, 2, 3));
		texture.trim();
		REQUIRE(texture.getBounds()->width == 2);
		REQUIRE(texture.getBounds()->height == 2);
		REQUIRE(texture.getOffsetX() == 0);
		REQUIRE(texture.getOffsetY() == 0);
		REQUIRE(texture.getSourceWidth() == 2);
		REQUIRE(texture.getSourceHeight() == 3);
	}

	SECTION("All sides")
	{
		Color4 raw[] =
		{
			{ 0,0,0,0 },{   0,0,  0,  0 },{   0,  0,  0,  0 },{ 0,0,0,0 },
			{ 0,0,0,0 },{ 255,0,  0,255 },{   0,255,  0,255 },{ 0,0,0,0 },
			{ 0,0,0,0 },{   0,0,255,255 },{ 255,  0,255,255 },{ 0,0,0,0 },
			{ 0,0,0,0 },{   0,0,  0,  0 },{   0,  0,  0,  0 },{ 0,0,0,0 }
		};

		Texture texture;
		REQUIRE(texture.loadFromMemory(raw, 4, 4));
		texture.trim();
		REQUIRE(texture.getBounds()->width == 2);
		REQUIRE(texture.getBounds()->height == 2);
		REQUIRE(texture.getOffsetX() == 1);
		REQUIRE(texture.getOffsetY() == 1);
		REQUIRE(texture.getSourceWidth() == 4);
		REQUIRE(texture.getSourceHeight() == 4);
	}
}

TEST_CASE("Texture can be rotated", "[TXPK/Core/Texture]")
{
	using namespace txpk;

	/*
	A B
	C D
	E F
	*/
	Color4 raw[] =
	{
		{ 0,0,0,1 },{ 0,0,0,2 },
		{ 0,0,0,3 },{ 0,0,0,4 },
		{ 0,0,0,5 },{ 0,0,0,6 }
	};

	Texture texture;
	REQUIRE(texture.loadFromMemory(raw, 2, 3));
	
	//this is actually kind of sloppy because you can only adjust the texture if the rectangle was rotated before
	//BUT no one holds you back to rotate the texture multiple times if the rectangle was rotated. 
	//This texture was not made for actual transformations
	//just rotating it 90° ccw if the rectangle got rotated
	//will probably be adjusted in the future, if someone does need it for some reason
	
	texture.getBounds()->rotate();
	texture.adjustRotation();

	/*
	B D F
	A C E
	*/
	Color4 expectedRaw[] =
	{
		{ 0,0,0,2 },{ 0,0,0,4 },{ 0,0,0,6 },
		{ 0,0,0,1 },{ 0,0,0,3 },{ 0,0,0,5 }
	};

	REQUIRE(array_equals(&texture.getRawPixelData()[0], expectedRaw, 6));
}

TEST_CASE("Textures can be compared on equality", "[TXPK/Core/Texture]")
{
	using namespace txpk;

	Color4 raw1[] =
	{
		{ 0,0,0,1 },{ 0,0,0,2 },
		{ 0,0,0,3 },{ 0,0,0,4 },
		{ 0,0,0,5 },{ 0,0,0,6 }
	};

	Color4 raw2[] =
	{
		{ 0,0,0,2 },{ 0,0,0,4 },{ 0,0,0,6 },
		{ 0,0,0,1 },{ 0,0,0,3 },{ 0,0,0,5 }
	};

	Color4 raw3[] =
	{
		{ 0,0,0, 7 },{ 0,0,0, 8 },
		{ 0,0,0, 9 },{ 0,0,0,10 },
		{ 0,0,0,11 },{ 0,0,0,12 }
	};

	Texture texture1;
	Texture texture2;

	SECTION("Not the same size")
	{
		texture1.loadFromMemory(raw1, 2, 3);
		texture2.loadFromMemory(raw2, 3, 2);
		REQUIRE(texture1 != texture2);

		texture1.getBounds()->rotate();
		texture1.adjustRotation();
		REQUIRE(texture1 == texture2);
	}

	SECTION("Same size and equal")
	{
		texture1.loadFromMemory(raw1, 2, 3);
		texture2.loadFromMemory(raw1, 2, 3);
		REQUIRE(texture1 == texture2);
	}
	
	SECTION("Same size but unequal")
	{
		texture1.loadFromMemory(raw1, 2, 3);
		texture2.loadFromMemory(raw3, 2, 3);
		REQUIRE(texture1 != texture2);
	}
}