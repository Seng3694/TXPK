#include <fstream>

#include "JsonConverter.h"

void JsonConverter::saveToJson(const std::string &path, const Bin &bin)
{
	std::ofstream stream;

	stream.open(path + "/atlas.json");

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