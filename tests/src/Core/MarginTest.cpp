#include <catch2/catch.hpp>

#include <TXPK/Core/Margin.hpp>

TEST_CASE("Margin can be constructed", "[TXPK/Core/Margin]")
{
	typedef txpk::Margin Margin;

	SECTION("With no parameters")
	{
		Margin margin;
		REQUIRE(margin.left == 0);
		REQUIRE(margin.top == 0);
		REQUIRE(margin.right == 0);
		REQUIRE(margin.bottom == 0);
	}

	SECTION("With one parameter")
	{
		Margin margin(10);
		REQUIRE(margin.left == 10);
		REQUIRE(margin.top == 10);
		REQUIRE(margin.right == 10);
		REQUIRE(margin.bottom == 10);
	}

	SECTION("With four parameters")
	{
		Margin margin(1, 2, 3, 4);
		REQUIRE(margin.left == 1);
		REQUIRE(margin.top == 2);
		REQUIRE(margin.right == 3);
		REQUIRE(margin.bottom == 4);
	}
}