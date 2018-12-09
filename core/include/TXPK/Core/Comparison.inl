#pragma once

#include "TXPK/Core/Comparison.hpp"

namespace txpk
{
	template<typename T>
	bool equals(const T* lhs, const T* rhs)
	{
		return memcmp(lhs, rhs, sizeof(T)) == 0;
	}

	template<typename T>
	bool array_equals(const T* lhs, const T* rhs, const uint32& objectCount)
	{
		return memcmp(lhs, rhs, sizeof(T) * objectCount) == 0;
	}

	template<uint32 size, typename T>
	bool array_equals(const T* lhs, const T* rhs)
	{
		return memcmp(lhs, rhs, sizeof(T) * size) == 0;
	}
}
