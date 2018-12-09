#include <catch2/catch.hpp>

#include <TXPK/KeyConverters/EnumeratorConverter.hpp>

TEST_CASE("EnumeratorConverter test", "[TXPK/KeyConverters/EnumeratorConverter]")
{
	using namespace txpk;

	const KeyConverterPtr converter = std::make_unique<EnumeratorConverter>();

	REQUIRE(converter->convert("hello_123.lua") == "0");
	REQUIRE(converter->convert("hello.lua") == "1");
	REQUIRE(converter->convert("hello") == "2");
	REQUIRE(converter->convert("seems like an enumerator") == "3");

	converter->reset();

	REQUIRE(converter->convert("hello") == "0");
}
