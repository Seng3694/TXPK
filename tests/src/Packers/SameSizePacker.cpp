#include <catch2/catch.hpp>

#include <TXPK/Packers/SameSizePacker.hpp>

TEST_CASE("SameSizePacker without constraint", "[TXPK/Packers/SameSizePacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<txpk::SameSizePacker>();

	SECTION("squared count")
	{
		uint32 count = 16;
		uint32 width = 32;
		uint32 height = 32;

		RectanglePtrs rects(count);
		for (uint32 i = 0; i < count; ++i)
			rects[i] = std::make_shared<txpk::Rectangle>(txpk::Rectangle(width, height));

		Bin bin = packer->pack(rects);
		REQUIRE(bin.width == static_cast<uint32>(sqrt(count) * width));
		REQUIRE(bin.height == static_cast<uint32>(sqrt(count) * height));
	}

	SECTION("prime count")
	{
		uint32 count = 7;
		uint32 width = 32;
		uint32 height = 32;

		RectanglePtrs rects(count);
		for (uint32 i = 0; i < count; ++i)
			rects[i] = std::make_shared<txpk::Rectangle>(txpk::Rectangle(width, height));

		Bin bin = packer->pack(rects);
		//should be packed in 4 * 2
		REQUIRE(bin.width == static_cast<uint32>(4 * width));
		REQUIRE(bin.height == static_cast<uint32>(2 * height));
	}

	SECTION("non squared non prime count")
	{
		uint32 count = 12;
		uint32 width = 32;
		uint32 height = 32;

		RectanglePtrs rects(count);
		for (uint32 i = 0; i < count; ++i)
			rects[i] = std::make_shared<txpk::Rectangle>(txpk::Rectangle(width, height));

		Bin bin = packer->pack(rects);
		//12 => 2 * 2 * 3 => 4 * 3
		REQUIRE(bin.width == static_cast<uint32>(4 * width));
		REQUIRE(bin.height == static_cast<uint32>(3 * height));
	}
}

TEST_CASE("SameSizePacker with width constraint", "[TXPK/Packers/SameSizePacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<SameSizePacker>();

	uint32 count = 16;
	uint32 width = 32;
	uint32 height = 32;
	uint32 constraint = 64;

	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = std::make_shared<txpk::Rectangle>(txpk::Rectangle(width, height));

	Bin bin = packer->pack(rects, constraint, SizeContraintType::Width);
	REQUIRE(bin.width == constraint);
	REQUIRE(bin.height == (count / (constraint / width)) * height);
}

TEST_CASE("SameSizePacker with height constraint", "[TXPK/Packers/SameSizePacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<SameSizePacker>();

	uint32 count = 16;
	uint32 width = 32;
	uint32 height = 32;
	uint32 constraint = 64;

	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = std::make_shared<txpk::Rectangle>(txpk::Rectangle(width, height));

	Bin bin = packer->pack(rects, constraint, SizeContraintType::Height);
	REQUIRE(bin.height == constraint);
	REQUIRE(bin.width == (count / (constraint / height)) * width);
}

//in case you want to pack texture with 40x40 in a texture with width 64
TEST_CASE("SameSizePacker with non fitting width constraint", "[TXPK/Packers/SameSizePacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<SameSizePacker>();

	uint32 count = 16;
	uint32 width = 40;
	uint32 height = 50;
	uint32 constraint = 64;

	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = std::make_shared<txpk::Rectangle>(txpk::Rectangle(width, height));

	Bin bin = packer->pack(rects, constraint, SizeContraintType::Width);
	REQUIRE(bin.width == constraint);
	REQUIRE(bin.height == (count / (constraint / width)) * height);
}

//in case you want to pack texture with 40x40 in a texture with height 64
TEST_CASE("SameSizePacker with non fitting height constraint", "[TXPK/Packers/SameSizePacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<SameSizePacker>();

	uint32 count = 16;
	uint32 width = 40;
	uint32 height = 50;
	uint32 constraint = 64;

	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = std::make_shared<txpk::Rectangle>(txpk::Rectangle(width, height));

	Bin bin = packer->pack(rects, constraint, SizeContraintType::Height);
	REQUIRE(bin.height == constraint);
	REQUIRE(bin.width == (count / (constraint / height)) * width);
}
