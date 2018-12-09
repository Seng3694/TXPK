#include <catch2/catch.hpp>

#include <TXPK/Core/StringExtension.hpp>

TEST_CASE("ends with", "[TXPK/Core/StringExtension]")
{
	using namespace txpk;

	const char* string = "helloworld.txt";

	REQUIRE(ends_with(string, "t"));
	REQUIRE(ends_with(string, ".txt"));
	REQUIRE(ends_with(string, "helloworld.txt"));
	REQUIRE(!ends_with(string, "png"));
}

TEST_CASE("string to int", "[TXPK/Core/StringExtension]")
{
	using namespace txpk;

	SECTION("decimal number string to int (base default)")
	{
		const char* string = "123";
		int32 out = 0;
		ConversionResult result = stoi(&out, string);
		REQUIRE(result == ConversionResult::Success);
		REQUIRE(out == 123);

		SECTION("interpreted as base 4")
		{
			ConversionResult result = stoi(&out, string, 4);
			REQUIRE(result == ConversionResult::Success);
			REQUIRE(out == 27);
		}

		SECTION("interpreted as base 3 (inconvertible)")
		{
			ConversionResult result = stoi(&out, string, 3);
			REQUIRE(result == ConversionResult::Inconvertible);
		}
	}
	
	SECTION("decimal overflow")
	{
		const char* string = "2147483649"; //should be one more than int32 max
		int32 out = 0;
		ConversionResult result = stoi(&out, string);
		REQUIRE(result == ConversionResult::Overflow);
	}

	SECTION("decimal underflow")
	{
		const char* string = "-2147483650"; //should be one less than int32 min
		int32 out = 0;
		ConversionResult result = stoi(&out, string);
		REQUIRE(result == ConversionResult::Underflow);
	}

	SECTION("hex string conversion")
	{
		const char* string = "DeadB0b";
		int32 out = 0; 
		ConversionResult result = stoi(&out, string);
		REQUIRE(result == ConversionResult::Success);
		REQUIRE(out == 233495307);
	}

	SECTION("alternative hex string conversion")
	{
		const char* string = "0xDeadB0b";
		int32 out = 0;
		ConversionResult result = stoi(&out, string);
		REQUIRE(result == ConversionResult::Success);
		REQUIRE(out == 233495307);
	}

	SECTION("base64 conversion")
	{
		const char* string = "MTMzNw==";
		int32 out = 0;
		ConversionResult result = stoi(&out, string);
		REQUIRE(result == ConversionResult::Success);
		REQUIRE(out == 1337);
	}
}