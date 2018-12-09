#include <catch2/catch.hpp>
#include <random>

#include <TXPK/Packers/BlackspawnPacker.hpp>

txpk::RectanglePtr generateRandomRectangle(const txpk::uint32 minWidth, const txpk::uint32 minHeight, const txpk::uint32 maxWidth, const txpk::uint32 maxHeight);

TEST_CASE("BlackspawnPacker without constraint no flip", "[TXPK/Packers/BlackspawnPacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<BlackspawnPacker>();

	uint32 count = 100;
	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = generateRandomRectangle(10, 10, 50, 50);

	Bin bin = packer->pack(rects);

	uint64 wholeArea = 0;
	for (uint32 i = 0; i < rects.size(); ++i)
		wholeArea += rects[i]->getArea();
	uint32 sqr = static_cast<uint32>(sqrt(wholeArea));

	REQUIRE(bin.height >= sqr);
	REQUIRE(bin.width >= sqr);
	REQUIRE(bin.height == bin.width);

	for (uint32 i = 0; i < bin.rectangles.size(); ++i)
		REQUIRE(bin.rectangles[i]->isRotated() == false);
}

TEST_CASE("BlackspawnPacker without constraint with flip", "[TXPK/Packers/BlackspawnPacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<BlackspawnPacker>();

	uint32 count = 1000;
	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = generateRandomRectangle(5, 5, 30, 30);

	Bin bin = packer->pack(rects, 0, SizeContraintType::None, true);

	uint64 wholeArea = 0;
	for (uint32 i = 0; i < rects.size(); ++i)
		wholeArea += rects[i]->getArea();
	uint32 sqr = static_cast<uint32>(sqrt(wholeArea));

	REQUIRE(bin.height >= sqr);
	REQUIRE(bin.width >= sqr);
	REQUIRE(bin.height == bin.width);

	bool isAnyFlipped = false;
	for (uint32 i = 0; i < bin.rectangles.size(); ++i)
		if (bin.rectangles[i]->isRotated())
			isAnyFlipped = true;

	//actually you could get unlucky because when the random generator generated textures which perfectly fit without flipping, there are no flips
	//thats why 1000 rectangles are generated
	REQUIRE(isAnyFlipped == true);
}

TEST_CASE("BlackspawnPacker with width constraint no flip", "[TXPK/Packers/BlackspawnPacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<BlackspawnPacker>();

	uint32 count = 100;
	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = generateRandomRectangle(10, 10, 50, 50);

	Bin bin = packer->pack(rects, 70, SizeContraintType::Width);

	uint64 wholeArea = 0;
	for (uint32 i = 0; i < rects.size(); ++i)
		wholeArea += rects[i]->getArea();

	REQUIRE(bin.width == 70);
	REQUIRE(bin.height >= (wholeArea / 70));

	for (uint32 i = 0; i < bin.rectangles.size(); ++i)
		REQUIRE(bin.rectangles[i]->isRotated() == false);
}

TEST_CASE("BlackspawnPacker with width constraint with flip", "[TXPK/Packers/BlackspawnPacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<BlackspawnPacker>();

	uint32 count = 1000;
	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = generateRandomRectangle(5, 5, 30, 30);

	Bin bin = packer->pack(rects, 70, SizeContraintType::Width, true);

	uint64 wholeArea = 0;
	for (uint32 i = 0; i < rects.size(); ++i)
		wholeArea += rects[i]->getArea();

	REQUIRE(bin.width == 70);
	REQUIRE(bin.height >= (wholeArea / 70));

	bool isAnyFlipped = false;

	for (uint32 i = 0; i < bin.rectangles.size(); ++i)
		if (bin.rectangles[i]->isRotated())
			isAnyFlipped = true;

	REQUIRE(isAnyFlipped == true);
}

TEST_CASE("BlackspawnPacker with height constraint no flip", "[TXPK/Packers/BlackspawnPacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<BlackspawnPacker>();

	uint32 count = 100;
	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = generateRandomRectangle(10, 10, 50, 50);

	Bin bin = packer->pack(rects, 70, SizeContraintType::Height);

	uint64 wholeArea = 0;
	for (uint32 i = 0; i < rects.size(); ++i)
		wholeArea += rects[i]->getArea();

	REQUIRE(bin.height == 70);
	REQUIRE(bin.width >= (wholeArea / 70));

	for (uint32 i = 0; i < bin.rectangles.size(); ++i)
		REQUIRE(bin.rectangles[i]->isRotated() == false);
}

TEST_CASE("BlackspawnPacker with height constraint with flip", "[TXPK/Packers/BlackspawnPacker]")
{
	using namespace txpk;

	const PackerPtr packer = std::make_unique<BlackspawnPacker>();

	uint32 count = 1000;
	RectanglePtrs rects(count);
	for (uint32 i = 0; i < count; ++i)
		rects[i] = generateRandomRectangle(5, 5, 30, 30);

	Bin bin = packer->pack(rects, 70, SizeContraintType::Height, true);

	uint64 wholeArea = 0;
	for (uint32 i = 0; i < rects.size(); ++i)
		wholeArea += rects[i]->getArea();

	REQUIRE(bin.height == 70);
	REQUIRE(bin.width >= (wholeArea / 70));

	bool isAnyFlipped = false;

	for (uint32 i = 0; i < bin.rectangles.size(); ++i)
		if (bin.rectangles[i]->isRotated())
			isAnyFlipped = true;

	REQUIRE(isAnyFlipped == true);
}

txpk::RectanglePtr generateRandomRectangle(const txpk::uint32 minWidth, const txpk::uint32 minHeight, const txpk::uint32 maxWidth, const txpk::uint32 maxHeight)
{
	txpk::uint32 width = (rand() % (maxWidth + 1));
	width = width < minWidth ? minWidth : width;
	txpk::uint32 height = (rand() % (maxHeight + 1));
	height = height < minHeight ? minHeight : width;
	return std::make_shared<txpk::Rectangle>(txpk::Rectangle(width, height));
}
