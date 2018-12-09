#include <catch2/catch.hpp>

#include <TXPK/KeyConverters/FileWithoutExtConverter.hpp>

TEST_CASE("FileWithoutExtConverter test", "[TXPK/KeyConverters/FileWithoutExtConverter]")
{
	const txpk::KeyConverterPtr converter = std::make_unique<txpk::FileWithoutExtConverter>();

	REQUIRE(converter->convert("hello.lua") == "hello");
	REQUIRE(converter->convert("some/path/to/file/hello.lua") == "hello");
}
