#include <fstream>
#include <iostream>
#include <string>

#include "JsonConverter.h"

void JsonConverter::saveToJson(const std::string &path, const std::string &fileName, const Bin &bin)
{
	std::ofstream stream;

	stream.open(path + "/" + fileName + ".json");

	stream << "{";
	stream << "\"path\":\"" << path << "\",";
	stream << "\"bin\":[";

	for (unsigned int i = 0; i < bin.infos.size(); i++)
	{
		stream << "{";
		stream << *bin.infos[i];

		if (i != bin.infos.size() - 1)
			stream << "},";
		else
			stream << "}";
	}

	stream << "]}";

	stream.close();
}