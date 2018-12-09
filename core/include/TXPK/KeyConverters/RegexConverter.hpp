#pragma once

#include <regex>

#include "TXPK/Core/IKeyConverter.hpp"

namespace txpk
{
	/**
	* \brief A converter which extracts the matching string out of the input and returns the result as a key.
	*/
	class RegexConverter : public IKeyConverter
	{
	public:
		RegexConverter(const std::string& regex);

		std::string convert(const std::string& input) override;
		void reset() override;

	private:
		std::regex regex;
	};
}
