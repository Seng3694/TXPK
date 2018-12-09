#include <catch2/catch.hpp>

#include <TXPK/KeyConverters/LuaConverter.hpp>

TEST_CASE("LuaConverter test", "[TXPK/KeyConverters/LuaConverter]")
{
	using namespace txpk;

	const KeyConverterPtr converter = std::make_unique<LuaConverter>(LuaConverter("content/CustomEnumeratorKeyConverter.lua"));

	REQUIRE(converter->convert("hello_123.lua") == "0");
	REQUIRE(converter->convert("hello.lua") == "1");
	REQUIRE(converter->convert("hello") == "2");
	REQUIRE(converter->convert("seems like an enumerator") == "3");

	converter->reset();

	REQUIRE(converter->convert("hello") == "0");
}

TEST_CASE("LuaConverter without reset defined", "[TXPK/KeyConverters/LuaConverter]")
{
	using namespace txpk;

	const KeyConverterPtr converter = std::make_unique<LuaConverter>(LuaConverter("content/WithoutResetKeyConverter.lua"));

	REQUIRE(converter->convert("hello_123.lua") == "hello_123.lua");
	REQUIRE(converter->convert("hello.lua") == "hello.lua");
	REQUIRE(converter->convert("hello") == "hello");
	REQUIRE(converter->convert("seems like an enumerator") == "seems like an enumerator");

	converter->reset();

	REQUIRE(converter->convert("hello") == "hello");
}
