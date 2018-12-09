#include <catch2/catch.hpp>

#include <TXPK/Core/Color.hpp>

TEST_CASE("Color can be constructed", "[TXPK/Core/Color]")
{
	using namespace txpk;

	SECTION("With one")
	{
		Color<1> color{ 0 };
		REQUIRE(color.data[0] == 0);
		REQUIRE(sizeof(Color<1>) == sizeof(uint8));
	}

	SECTION("With four")
	{
		Color<4> color{ 0, 0, 0, 0 };
		REQUIRE(color.data[0] == 0);
		REQUIRE(color.data[1] == 0);
		REQUIRE(color.data[2] == 0);
		REQUIRE(color.data[3] == 0);
		REQUIRE(sizeof(Color<4>) == (4 * sizeof(uint8)));
	}
}

TEST_CASE("Color is directly accessable via bracket operator", "[TXPK/Core/Color]")
{
	typedef txpk::Color<3> Color3;

	Color3 color;
	REQUIRE(color.data[0] == color[0]);
	REQUIRE(color.data[1] == color[1]);
	REQUIRE(color.data[2] == color[2]);

	color[0] = 1;
	color[1] = 2;
	color[2] = 3;

	REQUIRE(color.data[0] == 1);
	REQUIRE(color.data[1] == 2);
	REQUIRE(color.data[2] == 3);
}

TEST_CASE("Color can be checked on equality", "[TXPK/Core/Color]")
{
	typedef txpk::Color<3> Color3;

	Color3 a = { 1, 2, 3 };
	Color3 b = { 1, 2, 3 };

	REQUIRE((a == b) == true);
	REQUIRE((a != b) == false);
	b[2] = 1;
	REQUIRE((a == b) == false);
	REQUIRE((a != b) == true);
}