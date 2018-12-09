#include <catch2/catch.hpp>

#include <TXPK/FileSystem/FileSystem.hpp>

TEST_CASE("get_directory tests", "[TXPK/FileSystem/FileSystem]")
{
	using namespace txpk;

	REQUIRE(get_directory("") == ".");
	REQUIRE(get_directory("C:") == "C:");
	REQUIRE(get_directory("C:/Users") == "C:/Users");
	REQUIRE(get_directory("C:\\Users") == "C:/Users");
	REQUIRE(get_directory("C:/Users/User/Documents/bla.txt") == "C:/Users/User/Documents");
	REQUIRE(get_directory("C:\\Users\\User\\Documents\\bla.txt") == "C:/Users/User/Documents");
}


TEST_CASE("get_file_name tests", "[TXPK/FileSystem/FileSystem]")
{
	using namespace txpk;

	REQUIRE(get_file_name("") == "");
	REQUIRE(get_file_name("C:") == "");
	REQUIRE(get_file_name("C:/Users") == "");
	REQUIRE(get_file_name("C:\\Users") == "");
	REQUIRE(get_file_name("C:/Users/User/Documents/bla.txt") == "bla.txt");
	REQUIRE(get_file_name("C:\\Users\\User\\Documents\\bla.txt") == "bla.txt");
}

TEST_CASE("get_file_name_without_ext tests", "[TXPK/FileSystem/FileSystem]")
{
	using namespace txpk;

	REQUIRE(get_file_name_without_ext("") == "");
	REQUIRE(get_file_name_without_ext("C:") == "");
	REQUIRE(get_file_name_without_ext("C:/Users") == "");
	REQUIRE(get_file_name_without_ext("C:\\Users") == "");
	REQUIRE(get_file_name_without_ext("C:/Users/User/Documents/bla.txt") == "bla");
	REQUIRE(get_file_name_without_ext("C:\\Users\\User\\Documents\\bla.txt") == "bla");
}

TEST_CASE("get_file_extension tests", "[TXPK/FileSystem/FileSystem]")
{
	using namespace txpk;

	REQUIRE(get_file_extension("") == "");
	REQUIRE(get_file_extension("C:") == "");
	REQUIRE(get_file_extension("C:/Users") == "");
	REQUIRE(get_file_extension("C:\\Users") == "");
	REQUIRE(get_file_extension("C:/Users/User/Documents/bla.txt") == "txt");
	REQUIRE(get_file_extension("C:\\Users\\User\\Documents\\bla.txt") == "txt");
}

TEST_CASE("directory_exists tests", "[TXPK/FileSystem/FileSystem]")
{
	using namespace txpk;

	REQUIRE(directory_exists("") == true);
	REQUIRE(directory_exists(".") == true);
	REQUIRE(directory_exists("directory/which/does/not/exists") == false);
}

TEST_CASE("name_is_valid tests", "[TXPK/FileSystem/FileSystem]")
{
	using namespace txpk;

	REQUIRE(name_is_valid("") == false);
	REQUIRE(name_is_valid("test") == true);

	for (char i = '\0'; i < ' '; ++i)
	{
		std::string current;
		current.push_back(i);
		REQUIRE(name_is_valid(current) == false);
	}

	std::vector<char> invalidChars = { '<', '>', ':', '\"', '\\', '/', '|', '?', '*' };

	for (uint32 i = 0; i < invalidChars.size(); ++i)
	{
		std::string current;
		current.push_back(static_cast<char>(invalidChars[i]));
		REQUIRE(name_is_valid(current) == false);
	}
}

TEST_CASE("is_match tests", "[TXPK/FileSystem/FileSystem]")
{
	using namespace txpk;

	SECTION("With string")
	{
		REQUIRE(is_match("1234", "[0-9]+"));
		REQUIRE(!is_match("1234a", "[0-9]+"));

		//can't just write "/" in regex, so we have to escape it with a backslash "\/"
		//but we can't do that in c++ without escaping the backslash. Resulting in "\\/"
		std::string simpleUrlRegex("(http(s)?:\\/\\/)?[a-zA-Z]+\\.(com)(\\/[a-zA-Z0-9]+)*");
		REQUIRE(is_match("https://github.com/Seng3694/TXPK", simpleUrlRegex));
		REQUIRE(is_match("github.com/Seng3694/TXPK", simpleUrlRegex));
		REQUIRE(is_match("github.com", simpleUrlRegex));
	}

	SECTION("With regex")
	{
		std::regex r("[0-9]+");
		REQUIRE(is_match("1234", r));
		REQUIRE(!is_match("1234a", r));

		std::regex simpleUrlRegex("(http(s)?:\\/\\/)?[a-zA-Z]+\\.(com)(\\/[a-zA-Z0-9]+)*");
		REQUIRE(is_match("https://github.com/Seng3694/TXPK", simpleUrlRegex));
		REQUIRE(is_match("github.com/Seng3694/TXPK", simpleUrlRegex));
		REQUIRE(is_match("github.com", simpleUrlRegex));
	}
}

TEST_CASE("get_files tests", "[TXPK/FileSystem/FileSystem]")
{
	using namespace txpk;
	//cumbersome to test foreach platform
	//will probably test it in the future
}