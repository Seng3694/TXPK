#include "TXPK/Core/StringExtension.hpp"

namespace txpk
{
	ConversionResult stoi(int32& i, const char* s, int32 base)
	{
		char* end;
		long outValue;
		errno = 0;
		outValue = strtoul(s, &end, base);
		if ((errno == ERANGE && outValue == LONG_MAX) || outValue > UINT_MAX)
		{
			return ConversionResult::Overflow;
		}
		if ((errno == ERANGE && outValue == LONG_MIN) || outValue < INT_MIN)
		{
			return ConversionResult::Underflow;
		}
		if (*s == '\0' || *end != '\0')
		{
			return ConversionResult::Inconvertible;
		}

		i = static_cast<int32>(outValue);

		return ConversionResult::Success;
	}


	std::string alphanumeric_compare::getNumericPart(const std::string& str) const
	{
		std::string output;
		for (size_t i = 0; i < str.size(); ++i)
			if (str[i] >= '0' && str[i] <= '9')
				output.push_back(str[i]);
		return output;
	}

	std::string alphanumeric_compare::getAlphaPart(const std::string& str) const
	{
		std::string output;
		for (size_t i = 0; i < str.size(); ++i)
			if (str[i] < '0' || str[i] > '9')
				output.push_back(str[i]);
		return output;
	}

	bool alphanumeric_compare::operator()(const std::string& a, const std::string& b) const
	{
		std::string aAlpha = getAlphaPart(a);
		std::string bAlpha = getAlphaPart(b);

		if (aAlpha == bAlpha)
		{
			std::string aNumeric = getNumericPart(a);
			std::string bNumeric = getNumericPart(b);

			int32 ai = 0;
			int32 bi = 0;
			if (stoi(ai, aNumeric.c_str()) == ConversionResult::Success
				&& stoi(bi, bNumeric.c_str()) == ConversionResult::Success)
			{
				return ai < bi;
			}
		}

		return a < b;
	}
}
