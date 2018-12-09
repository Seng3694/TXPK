#pragma once

#include <sstream>

#include "TXPK/Core/Common.hpp"
#include "TXPK/Core/IKeyConverter.hpp"

namespace txpk
{
	/**
	* \brief A converter which does actually not convert but counts the convert calls and returns the number as a key.
	*/
	class EnumeratorConverter : public IKeyConverter
	{
	public:
		EnumeratorConverter();

		std::string convert(const std::string& input) override;
		void reset() override; /**< Resets the counter to zero */

	private:
		int32 i; /**< The counter variable */
	};
}
