#include "TXPK/FileSystem/FileNode.hpp"

namespace txpk
{
	FileNode::FileNode(const std::string& value)
	{
		this->parent = NULL;
		this->value = value;
	}

	std::string FileNode::getFullPath() const
	{
		size_t fullLength = 0;
		size_t nodeCount = 0;
		const FileNode* current = this;

		//counting all nodes up to root
		while (current != NULL)
		{
			fullLength += current->value.size();
			current = &(*current->parent);
			++nodeCount;
		}

		//resulting string has the length of all nodes 
		//   (fullLength) + 
		//a slash for each node but not for the last
		//   (nodeCount - 1)
		//resulting in (fullLength + nodeCount - 1)
		std::string path(fullLength + nodeCount - 1, 0);

		fullLength = path.size() + 1;
		current = this;
		//iterative building of the string. 
		//because we are starting at a leaf we have to build it up backwards
		for (size_t i = 0; i < nodeCount; ++i)
		{
			//fullLength serves kind of a current index of the result string
			//this calculation subtracts the size of the current node and one extra for the slash (or the \0 of the last node)
			fullLength = fullLength - current->value.size() - 1;

			//if it is not the root node, then prepend a slash
			if (i < nodeCount - 1)
				path[fullLength - 1] = '/';

			memcpy(&path[fullLength], &(current->value[0]), current->value.size());

			current = &(*current->parent);
		}

		return path;
	}

	std::string FileNode::getValue() const
	{
		return value;
	}
}
