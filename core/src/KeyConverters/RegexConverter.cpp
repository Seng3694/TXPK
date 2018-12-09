#pragma once

#include "TXPK/KeyConverters/RegexConverter.hpp"

namespace txpk
{
	RegexConverter::RegexConverter(const std::string& regex)
	{
		this->regex = std::regex(regex);
	}

	std::string RegexConverter::convert(const std::string& input)
	{
		std::smatch match;
		if (std::regex_search(input.begin(), input.end(), match, regex))
			return match[0];
		else
			return input;
	}

	void RegexConverter::reset()
	{
	}
}
