#include <catch2/catch.hpp>

#include <TXPK/FileSystem/FileNode.hpp>

TEST_CASE("File nodes are returning a correct path", "[TXPK/FileSystem/FileNode]")
{
	using namespace txpk;

	FileNode root("C:");

	FileNode node1("Users");
	node1.parent = std::make_shared<FileNode>(root);

	FileNode node2("SomeUser");
	node2.parent = std::make_shared<FileNode>(node1);

	FileNode node3("Documents");
	node3.parent = std::make_shared<FileNode>(node2);

	REQUIRE(root.getValue() == "C:");
	REQUIRE(root.getFullPath() == "C:");

	REQUIRE(node1.getValue() == "Users");
	REQUIRE(node1.getFullPath() == "C:/Users");

	REQUIRE(node2.getValue() == "SomeUser");
	REQUIRE(node2.getFullPath() == "C:/Users/SomeUser");

	REQUIRE(node3.getValue() == "Documents");
	REQUIRE(node3.getFullPath() == "C:/Users/SomeUser/Documents");
}
