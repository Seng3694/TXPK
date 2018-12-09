#pragma once

#include "TXPK/Core/Rectangle.hpp"

namespace txpk
{
	inline uint32 Rectangle::getRight() const
	{
		return left + width;
	}

	inline uint32 Rectangle::getBottom() const
	{
		return top + height;
	}

	inline uint32 Rectangle::getArea() const
	{
		return width * height;
	}

	inline uint32 Rectangle::getPerimeter() const
	{
		return 2 * width + 2 * height;
	}

	inline bool Rectangle::isRotated() const
	{
		return rotated;
	}
}
