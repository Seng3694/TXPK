#include <catch2/catch.hpp>

#include <TXPK/Core/Rectangle.hpp>


TEST_CASE("Rectangle can be constructed", "[TXPK/Core/Rectangle]")
{
	using namespace txpk;

	SECTION("With default constructor")
	{
		Rectangle rectangle;
		REQUIRE(rectangle.left == 0);
		REQUIRE(rectangle.top == 0);
		REQUIRE(rectangle.width == 0);
		REQUIRE(rectangle.height == 0);
		REQUIRE(rectangle.isRotated() == false);
		REQUIRE(rectangle.getArea() == 0);
		REQUIRE(rectangle.getRight() == 0);
		REQUIRE(rectangle.getBottom() == 0);
		REQUIRE(rectangle.getPerimeter() == 0);
	}

	SECTION("With width and height constructor")
	{
		Rectangle rectangle(10, 20);
		REQUIRE(rectangle.left == 0);
		REQUIRE(rectangle.top == 0);
		REQUIRE(rectangle.width == 10);
		REQUIRE(rectangle.height == 20);
		REQUIRE(rectangle.isRotated() == false);
		REQUIRE(rectangle.getArea() == 200);
		REQUIRE(rectangle.getRight() == 10);
		REQUIRE(rectangle.getBottom() == 20);
		REQUIRE(rectangle.getPerimeter() == 60);
	}

	SECTION("With left, top, right and bottom constructor")
	{
		Rectangle rectangle(10, 20, 30, 40);
		REQUIRE(rectangle.left == 10);
		REQUIRE(rectangle.top == 20);
		REQUIRE(rectangle.width == 20); //right - left
		REQUIRE(rectangle.height == 20); //bottom - top
		REQUIRE(rectangle.isRotated() == false);
		REQUIRE(rectangle.getArea() == 400);
		REQUIRE(rectangle.getRight() == 30);
		REQUIRE(rectangle.getBottom() == 40);
		REQUIRE(rectangle.getPerimeter() == 80);
	}
}

TEST_CASE("Rectangle can be rotated", "[TXPK/Core/Rectangle]")
{
	using namespace txpk;

	SECTION("Without any size")
	{
		Rectangle rectangle;
		rectangle.rotate();
		REQUIRE(rectangle.left == 0);
		REQUIRE(rectangle.top == 0);
		REQUIRE(rectangle.width == 0);
		REQUIRE(rectangle.height == 0);
		REQUIRE(rectangle.isRotated() == true);
		REQUIRE(rectangle.getArea() == 0);
		REQUIRE(rectangle.getRight() == 0);
		REQUIRE(rectangle.getBottom() == 0);
		REQUIRE(rectangle.getPerimeter() == 0);
	}

	SECTION("With any size")
	{
		Rectangle rectangle(10, 20);
		rectangle.rotate();
		REQUIRE(rectangle.left == 0);
		REQUIRE(rectangle.top == 0);
		REQUIRE(rectangle.width == 20); //because it got flipped, the width and height were swapped
		REQUIRE(rectangle.height == 10);
		REQUIRE(rectangle.isRotated() == true);
		REQUIRE(rectangle.getArea() == 200);
		REQUIRE(rectangle.getRight() == 20);
		REQUIRE(rectangle.getBottom() == 10);
		REQUIRE(rectangle.getPerimeter() == 60);
	}
}

TEST_CASE("Rectangle a can fit in rectangle b", "[TXPK/Core/Rectangle]")
{
	using namespace txpk;

	SECTION("a < b (normal)")
	{
		Rectangle a(10, 10);
		Rectangle b(20, 20);

		REQUIRE(a.fits(b, false) == FitResult::Yes);
		REQUIRE(a.fits(b, true) == FitResult::Yes);
	}

	SECTION("a == b (perfect)")
	{
		Rectangle a(10, 10);
		Rectangle b(10, 10);

		REQUIRE(a.fits(b, false) == FitResult::Perfect);
		REQUIRE(a.fits(b, true) == FitResult::Perfect);
	}

	SECTION("a(rotated) < b (rotated)")
	{
		Rectangle a(10, 20);
		Rectangle b(30, 10);

		REQUIRE(a.fits(b, false) == FitResult::No);
		REQUIRE(a.fits(b, true) == FitResult::Rotated);
	}

	SECTION("a(rotated) == b (perfect rotated)")
	{
		Rectangle a(10, 20);
		Rectangle b(20, 10);

		REQUIRE(a.fits(b, false) == FitResult::No);
		REQUIRE(a.fits(b, true) == FitResult::PerfectRotated);
	}
}
