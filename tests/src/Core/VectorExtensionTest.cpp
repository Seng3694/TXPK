#include <catch2/catch.hpp>

#include <TXPK/Core/VectorExtension.hpp>

TEST_CASE("Margin can be applied to raw pointer", "[TXPK/Core/VectorExtension]")
{
	using namespace txpk;

	//this is just for visualization purposes
	//you can't actually resize a const array
	int32 arr[] = 
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};

	//that's the pointer we are working on from now
	int32* copy = new int32[9];
	memcpy(copy, arr, 9 * sizeof(int32));

	Margin margin(1);
	/*
	      |1
		  v
	 1->     <-1
	      ^
		  |1
	*/
	apply_margin(&copy, 3, 3, margin);

	//should be just an array with one element
	REQUIRE(copy[0] == 5);
}

TEST_CASE("Margin can be applied to vector", "[TXPK/Core/VectorExtension]")
{
	using namespace txpk;

	int32 arr[] =
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};

	std::vector<int32> vector;
	for (uint32 i = 0; i < 9; ++i)
		vector.push_back(arr[i]);

	Margin margin(1);
	vector = apply_margin(vector, 3, 3, margin);

	REQUIRE(vector.size() == 1);
	REQUIRE(vector[0] == 5);
}
