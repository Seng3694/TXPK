#pragma once

#include <limits.h>
#include <string.h>
#include <string>

#include "TXPK/Core/Common.hpp"

namespace txpk
{
	/**
	* \brief The ConversionResult enum.
	* It will be returned as a result from a string to integer conversion.
	*/
	enum class ConversionResult
	{ 
		Success, /**< Conversion successful */
		Overflow, /**< String was representing a value larger than int.max */
		Underflow, /**< String was representing a value smaller than int.min */
		Inconvertible /**< The string could not be converted to a number */
	};

	/**
	* \brief Converts a string to an integer.
	* \param i The resulting integer value.
	* \param s The string to convert.
	* \param base The base the number is represented in the string. Choose zero if it should be auto detected.
	* \return Returns a result whether the conversion was successful or not.
	*/
	ConversionResult stoi(int32& i, const char* s, int32 base = 0);

	/**
	* \brief Checks whether a string ends with another string or not.
	* \param str The string to check.
	* \param ext The extension which should be searched for in the string.
	* \return Returns if the string ends with the extension.
	*/
	inline bool ends_with(const char* str, const char* ext);

	/**
	* \brief The alphanumeric comparison struct.
	*/
	struct alphanumeric_compare
	{
		/**
		* \brief Extracts all numeric characters out of the string.
		* \param str The string to extract from.
		* \return Returns the numeric characters as a string.
		*/
		std::string getNumericPart(const std::string& str) const;
		/**
		* \brief Extracts all non numeric characters out of the string.
		* \param str The string to extract from.
		* \return Returns the non numeric characters as a string.
		*/
		std::string getAlphaPart(const std::string& str) const;
		/**
		* \brief The operator() which compares to strings first by numbers then by non numbers.
		* Can be used as a std::map comparer.
		* \param a First string.
		* \param b Second string.
		* \return Returns if a is "larger" than b.
		*/
		bool operator()(const std::string& a, const std::string& b) const;
	};
}

#include "TXPK/Core/StringExtension.inl"
