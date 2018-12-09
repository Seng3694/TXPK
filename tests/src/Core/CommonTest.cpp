#include <catch2/catch.hpp>

#include <TXPK/Core/Common.hpp>

enum class Colors
{
	None  = 0,
	Red	  = 1 << 0,
	Green = 1 << 1,
	Blue  = 1 << 2
};

TEST_CASE("Common checks", "[TXPK/Core/Common]")
{
	using namespace txpk;

	REQUIRE(sizeof(int8)	 == sizeof(signed char));
	REQUIRE(sizeof(uint8)	 == sizeof(unsigned char));
	REQUIRE(sizeof(int16)	 == sizeof(signed short));
	REQUIRE(sizeof(uint16)	 == sizeof(unsigned short));
	REQUIRE(sizeof(int32)	 == sizeof(signed int));
	REQUIRE(sizeof(uint32)   == sizeof(unsigned int));
	REQUIRE(sizeof(int64)	 == sizeof(signed long long));
	REQUIRE(sizeof(uint64)   == sizeof(unsigned long long));

	SECTION("Enum flags HAS_FLAG")
	{
		Colors colors = static_cast<Colors>(static_cast<int>(Colors::Red) | static_cast<int>(Colors::Green));
		REQUIRE(colors != Colors::None);
		REQUIRE(HAS_FLAG(static_cast<int>(colors), static_cast<int>(Colors::Red)));
		REQUIRE(HAS_FLAG(static_cast<int>(colors), static_cast<int>(Colors::Green)));
		REQUIRE(!HAS_FLAG(static_cast<int>(colors), static_cast<int>(Colors::Blue)));
	}
}

GENERATE_FLAGS_OPERATORS(Colors);

TEST_CASE("Flags generation", "[TXPK/Core/Common]")
{
	//because that casting is cumbersome...
	Colors colors = Colors::Red | Colors::Green;
	REQUIRE(colors != Colors::None);
	REQUIRE(HAS_FLAG(colors, Colors::Red));
	REQUIRE(HAS_FLAG(colors, Colors::Green));
	REQUIRE(!HAS_FLAG(colors, Colors::Blue));
}