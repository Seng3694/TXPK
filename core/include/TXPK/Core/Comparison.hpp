#pragma once

#include <cstring>

#include "TXPK/Core/Common.hpp"

namespace txpk
{
	/**
	* \brief Checks if two values are the same.
	* Checks the bytes internally with memcmp.
	* \param lhs Pointer to the first value.
	* \param rhs Pointer to the second value.
	* \return Returns true if both values are equal and false if not.
	*/
	template<typename T>
	bool equals(const T* lhs, const T* rhs);

	/**
	* \brief Checks if two arrays are the same.
	* Checks the bytes internally with memcmp.
	* \param lhs Pointer to the first array.
	* \param rhs Pointer to the second array.
	* \param objectCount The count of the items to check.
	* \return Returns true if both arrays are equal and false if not.
	*/
	template<typename T>
	bool array_equals(const T* lhs, const T* rhs, const uint32& objectCount);

	/**
	* \brief Checks if two arrays are the same.
	* Checks the bytes internally with memcmp. Useful overload if you know how many items to check at compile time.
	* \tparam The count of the items to check.
	* \param lhs Pointer to the first array.
	* \param rhs Pointer to the second array.
	* \return Returns true if both arrays are equal and false if not.
	*/
	template<uint32 size, typename T>
	bool array_equals(const T* lhs, const T* rhs);
}

#include "TXPK/Core/Comparison.inl"
