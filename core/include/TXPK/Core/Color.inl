#pragma once

#include "TXPK/Core/Color.hpp"

namespace txpk
{
	template<uint32 size>
	uint8 Color<size>::operator [](const int32 index) const
	{
		return data[index];
	}

	template<uint32 size>
	uint8& Color<size>::operator [](const int32 index)
	{
		return data[index];
	}

	template<uint32 size>
	bool Color<size>::operator ==(const Color<size>& other)
	{
		return array_equals<size>(data, other.data);
	}

	template<uint32 size>
	bool Color<size>::operator !=(const Color<size>& other)
	{
		return !array_equals<size>(data, other.data);
	}
}
