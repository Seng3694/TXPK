#pragma once

#include <memory>
#include <string.h>
#include <string>

namespace txpk
{
	/**
	* \brief Class which represents a part of a file path.
	* e.g.: "C:/Users/User/Documents/MyDocument.txt" would consist of 5 different nodes:
	* "C:", "Users", "User", "Documents", "MyDocument.txt"
	*/
	class FileNode
	{
	public:
		std::shared_ptr<FileNode> parent; /**< The parent node in file tree. If this node is the root the parent node will be NULL. */

		/**
		* \brief Constructs a file node.
		* \param value The name/value of the node.
		*/
		FileNode(const std::string& value);
		/**
		* \brief Builds the whole path from this node down to the root.
		* \return Returns the whole path as a string.
		*/
		std::string getFullPath() const;
		/**
		* \brief Gets the name/value of this node.
		* \return Returns the string containing the name/value of this node.
		*/
		std::string getValue() const;

	private:
		std::string value; /**< The name/value of this node */
	};
}
