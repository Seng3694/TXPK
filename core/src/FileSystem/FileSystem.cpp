#include "TXPK/FileSystem/FileSystem.hpp"
#include "TXPK/Core/StringExtension.hpp"

namespace txpk
{
	void get_files(const std::string& directory, const std::regex& regex, bool recursive, std::vector<std::shared_ptr<FileNode>>& nodes, std::shared_ptr<FileNode> currentNode);
	void get_files(const std::string& directory, bool recursive, std::vector<std::shared_ptr<FileNode>>& nodes, std::shared_ptr<FileNode> currentNode);
	
	std::string get_directory(std::string path)
	{
		if (path == "")
			return std::string(".");

		std::replace(path.begin(), path.end(), '\\', '/');

		size_t index = path.find_last_of('.');
		if (index == std::string::npos)
		{
			return path;
		}
		else
		{
			index = path.find_last_of('/');
			if (index == std::string::npos)
				return std::string(".");
			else
				return path.substr(0, index);

		}
	}

	std::string get_file_name(std::string path)
	{
		size_t index = path.find_last_of('.');
		if (index == std::string::npos)
			return std::string();

		std::replace(path.begin(), path.end(), '\\', '/');
		index = path.find_last_of('/');
		if (index == std::string::npos)
			return path;

		return path.substr(index + 1, path.size() - index - 1);
	}

	std::string get_file_name_without_ext(const std::string& path)
	{
		std::string name = get_file_name(path);
		size_t index = name.find_last_of('.');
		if (index == std::string::npos)
			return name;

		return name.substr(0, index);
	}

	std::string get_file_extension(const std::string& path)
	{
		std::string name = get_file_name(path);
		size_t index = name.find_last_of('.');
		if (index == std::string::npos)
			return name;

		return name.substr(index + 1, name.size() - index - 1);
	}

	bool directory_exists(const std::string& directory)
	{
		DIR* dir = opendir(directory == "" ? "./" : directory.c_str());

		if (dir)
		{
			closedir(dir);
			return true;
		}

		return false;
	}

	bool name_is_valid(const std::string& name)
	{
		if (name.size() == 0)
			return false;

		for (uint32 i = 0; i < name.size(); ++i)
		{
			if (name[i] <= 31)
				return false;
			if (name[i] == '<'
				|| name[i] == '>'
				|| name[i] == ':'
				|| name[i] == '\"'
				|| name[i] == '/'
				|| name[i] == '\\'
				|| name[i] == '|'
				|| name[i] == '?'
				|| name[i] == '*')
				return false;
		}

		return true;
	}

	bool is_match(const std::string& path, const std::string& regex)
	{
		std::regex r(regex);
		return is_match(path, r);
	}

	bool is_match(const std::string& path, const std::regex& regex)
	{
		try
		{
			return std::regex_match(path, regex);
		}
		catch (std::regex_error&)
		{
			return false;
		}
	}

	std::vector<std::shared_ptr<FileNode>> get_files(const std::string& directory, const std::string& regex, bool recursive)
	{
		std::vector<std::shared_ptr<FileNode>> nodes;
		std::shared_ptr<FileNode> node = std::make_shared<FileNode>(FileNode(directory == "" ? "." : directory));

		if (regex == "")
		{
			get_files(directory == "" ? "." : directory, recursive, nodes, node);
		}
		else
		{
			std::regex r(regex);
			get_files(directory == "" ? "." : directory, r, recursive, nodes, node);
		}

		return nodes;
	}

	void get_files(const std::string& directory, const std::regex& regex, bool recursive, std::vector<std::shared_ptr<FileNode>>& nodes, std::shared_ptr<FileNode> currentNode)
	{
		struct dirent** files;

		int count = scandir(directory.c_str(), &files, NULL, alphasort);
		if (count > 0)
		{
			for (size_t i = 0; i < static_cast<size_t>(count); ++i)
			{
				struct dirent *entry = files[i];

				switch (entry->d_type)
				{
				case DT_REG: //regular => file
				{
					if (is_match(entry->d_name, regex))
					{
						std::shared_ptr<FileNode> node = std::make_shared<FileNode>(FileNode(entry->d_name));
						node->parent = currentNode;
						nodes.push_back(node);
					}
					break;
				}
				case DT_DIR: //directory
				{
					if (recursive
						&& strcmp(entry->d_name, ".") != 0
						&& strcmp(entry->d_name, "..") != 0)
					{
						std::shared_ptr<FileNode> node = std::make_shared<FileNode>(FileNode(entry->d_name));
						node->parent = currentNode;
						get_files(node->getFullPath(), regex, recursive, nodes, node);
					}

					break;
				}
				}

				free(entry);
			}
		}

		free(files);
	}

	void get_files(const std::string& directory, bool recursive, std::vector<std::shared_ptr<FileNode>>& nodes, std::shared_ptr<FileNode> currentNode)
	{
		struct dirent** files;

		int count = scandir(directory.c_str(), &files, NULL, alphasort);
		if (count > 0)
		{
			for (size_t i = 0; i < static_cast<size_t>(count); ++i)
			{
				struct dirent *entry = files[i];

				switch (entry->d_type)
				{
				case DT_REG: //regular => file
				{
					std::shared_ptr<FileNode> node = std::make_shared<FileNode>(FileNode(entry->d_name));
					node->parent = currentNode;
					nodes.push_back(node);
					break;
				}
				case DT_DIR: //directory
				{
					if (recursive
						&& strcmp(entry->d_name, ".") != 0
						&& strcmp(entry->d_name, "..") != 0)
					{
						std::shared_ptr<FileNode> node = std::make_shared<FileNode>(FileNode(entry->d_name));
						node->parent = currentNode;
						get_files(node->getFullPath(), recursive, nodes, node);
					}

					break;
				}
				}

				free(entry);
			}
		}

		free(files);
	}
}
