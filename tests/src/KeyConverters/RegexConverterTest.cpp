#include <catch2/catch.hpp>

#include <TXPK/KeyConverters/RegexConverter.hpp>

TEST_CASE("RegexConverter test", "[TXPK/KeyConverters/RegexConverter]")
{
	using namespace txpk;

	const KeyConverterPtr converter = std::make_unique<RegexConverter>(RegexConverter("[0-9]+"));

	REQUIRE(converter->convert("hello_123.lua") == "123");
	REQUIRE(converter->convert("hello.lua") == "hello.lua");
}
