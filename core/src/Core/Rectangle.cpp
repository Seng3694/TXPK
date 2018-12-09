#include "TXPK/Core/Rectangle.hpp"

namespace txpk
{
	Rectangle::Rectangle()
	{
		left = 0;
		top = 0;
		width = 0;
		height = 0;
		rotated = false;
	}

	Rectangle::Rectangle(const uint32& width, const uint32& height)
	{
		this->width = width;
		this->height = height;
		left = 0;
		top = 0;
		rotated = false;
	}

	Rectangle::Rectangle(const uint32& left, const uint32& top, const uint32& right, const uint32& bottom)
	{
		this->left = left;
		this->top = top;
		width = right - left;
		height = bottom - top;
		rotated = false;
	}

	void Rectangle::rotate()
	{
		rotated = !rotated;
		width ^= height;
		height ^= width;
		width ^= height;
	}

	FitResult Rectangle::fits(const Rectangle& other, bool allowRotation) const
	{
		if (width == other.width && height == other.height) return FitResult::Perfect;
		if (allowRotation && height == other.width && width == other.height) return FitResult::PerfectRotated;
		if (width <= other.width && height <= other.height) return FitResult::Yes;
		if (allowRotation && height <= other.width && width <= other.height) return FitResult::Rotated;

		return FitResult::No;
	}

	bool Rectangle::operator ==(const Rectangle& other)
	{
		return width == other.width
			&& height == other.height;
	}

	bool Rectangle::operator !=(const Rectangle& other)
	{
		return width != other.width
			|| height != other.height;
	}
}
