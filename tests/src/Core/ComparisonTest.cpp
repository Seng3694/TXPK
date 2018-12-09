#include <catch2/catch.hpp>

#include <TXPK/Core/Comparison.hpp>

TEST_CASE("Equals", "[TXPK/Core/Comparison]")
{
	using namespace txpk;

	SECTION("Testing equality of primitive types")
	{
		int a = 10;
		int b = 10;
		REQUIRE(equals(&a, &b));
		b = 20;
		REQUIRE(!equals(&a, &b));
	}
	
	SECTION("Testing equality of struct types")
	{
		struct TestStruct
		{
			int x;
			int y;
		};

		TestStruct a = { 10, 10 };
		TestStruct b = { 10, 10 };
		REQUIRE(equals(&a, &b));
		b.x = 20;
		REQUIRE(!equals(&a, &b));
	}
}

TEST_CASE("Array Equals", "[TXPK/Core/Comparison]")
{
	using namespace txpk;

	int arr1[] = { 1, 2, 3, 4, 5 };
	int arr2[] = { 1, 2, 3, 4, 5 };

	SECTION("Test equality of two equal arrays")
	{
		//all five elements should be equal
		REQUIRE(array_equals(arr1, arr2, 5));
		//the first three ofc too
		REQUIRE(array_equals(arr1, arr2, 3));

		//static length
		REQUIRE(array_equals<5>(arr1, arr2));
		REQUIRE(array_equals<3>(arr1, arr2));
	}

	SECTION("Test equality of two unequal arrays")
	{
		arr2[4] = 4;

		//all five elements should be unequal now
		REQUIRE(!array_equals(arr1, arr2, 5));
		//but the first three should be still the same
		REQUIRE(array_equals(arr1, arr2, 3));

		//static length
		REQUIRE(!array_equals<5>(arr1, arr2));
		REQUIRE(array_equals<3>(arr1, arr2));
	}
}