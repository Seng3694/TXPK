#pragma once

#include <memory>
#include <string>

namespace txpk
{
	/**
	* \brief Interface used by all KeyConverter implementations.
	*/
	class IKeyConverter
	{
	public:
		/**
		* \brief Pure virtual interface needs a virtual destructor.
		*/
		virtual ~IKeyConverter() {}

		/**
		* \brief Converts the given string in the way the implementation is defined.
		* \param input The input string to convert.
		* \return 
		*/
		virtual std::string convert(const std::string& input) = 0;
		/**
		* \brief Resets any state in the converter.
		*/
		virtual void reset() = 0;
	};

	typedef std::shared_ptr<IKeyConverter> KeyConverterPtr;
}
