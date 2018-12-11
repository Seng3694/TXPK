#pragma once

#include <regex>
#include <string.h>
#include <string>

#include <dirent.h>

#include "TXPK/Core/Common.hpp"
#include "TXPK/FileSystem/FileNode.hpp"

namespace txpk
{
	/**
	* \brief Checks whether the path is relative or not.
	* \param path The path to check.
	* \return Returns true if the path is relative.
	*/
	bool is_relative(const std::string& path);
	/**
	* \brief Checks whether the path is absolute or not.
	* \param path The path to check.
	* \return Returns true if the path is absolute.
	*/
	bool is_absolute(const std::string& path);
	/**
	* \brief Extracts the directory out of the path.
	* "./some/directory/test.txt" => "./some/directory"
	* "test.txt" => ""
	* \param path The path to extract from.
	* \return Returns the extracted directory.
	*/
	std::string get_directory(std::string path);
	/**
	* \brief Extracts the file name out of the path.
	* "./some/directory/test.txt" => "test.txt"
	* "./some/directory" => ""
	* \param path The path to extract from.
	* \return Returns the extracted file name.
	*/
	std::string get_file_name(std::string path);
	/**
	* \brief Extracts the file name out of the path without the extension.
	* "./some/directory/test.txt" => "test"
	* "./some/directory" => ""
	* \param path The path to extract from.
	* \return Returns the extracted file name without extension.
	*/
	std::string get_file_name_without_ext(const std::string& path);
	/**
	* \brief Extracts the file extension out of the path.
	* "./some/directory/test.txt" => "txt"
	* "./some/directory" => ""
	* \param path The path to extract from.
	* \return Returns the extracted file extension.
	*/
	std::string get_file_extension(const std::string& path);
	/**
	* \brief Checks whether the given directory exists or not.
	* \param directory The directory path to check.
	* \return Returns true if the directory exists and false if not.
	*/
	bool directory_exists(const std::string& directory);
	/**
	* \brief Checks whether the file name has invalid characters or not.
	* \param name The file name to check.
	* \return Returns true if the name does not contain any invalid characters.
	*/
	bool name_is_valid(const std::string& name);
	/**
	* \brief Checks if the given string matches the regular expression.
	* \param path The string to check.
	* \param regex The regular expression to use.
	* \return Returns true if the regular expression matches the string.
	*/
	bool is_match(const std::string& path, const std::string& regex);
	/**
	* \brief Checks if the given string matches the regular expression.
	* \param path The string to check.
	* \param regex The regular expression to use.
	* \return Returns true if the regular expression matches the string.
	*/
	bool is_match(const std::string& path, const std::regex& regex);
	/**
	* \brief Builds a file node tree from the given directory as root and returns all leaves.
	* \param directory The root of the tree.
	* \param regex Optional regex to filter the files with.
	* \param recursive Whether the directories should be traversed recursively or not. If not only files in the first directory will be returned. 
	* \return Returns a vector of all file node leaves.
	*/
	std::vector<std::shared_ptr<FileNode>> get_files(const std::string& directory, const std::string& regex, bool recursive);
}
