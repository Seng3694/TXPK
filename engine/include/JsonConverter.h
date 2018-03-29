#pragma once

#include <string>

#include "Bin.h"

class JsonConverter
{
public:
	static void saveToJson(const std::string &path, const std::string &fileName, const Bin &bin);
};