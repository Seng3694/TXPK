#pragma once

#include "TXPK/KeyConverters/EnumeratorConverter.hpp"

namespace txpk
{
	EnumeratorConverter::EnumeratorConverter()
	{
		i = 0;
	}

	std::string EnumeratorConverter::convert(const std::string& input)
	{
		std::stringstream ss;
		ss << i;
		i++;
		return ss.str();
	}

	void EnumeratorConverter::reset()
	{
		i = 0;
	}
}
