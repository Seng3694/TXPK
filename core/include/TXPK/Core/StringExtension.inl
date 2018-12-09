#pragma once

#include "TXPK/Core/StringExtension.hpp"

namespace txpk
{
	bool ends_with(const char* str, const char* ext)
	{
		const size_t strLength = strlen(str);
		const size_t extLength = strlen(ext);
		return memcmp(str + strLength - extLength, ext, extLength) == 0;
	}
}
