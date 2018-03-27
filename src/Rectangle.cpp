#include "Rectangle.h"

Rectangle::Rectangle()
	: left(0), top(0), width(0), height(0), _isFlipped(false)
{
}

Rectangle::Rectangle(const int & w, const int & h)
	: left(0), top(0), width(w), height(h), _isFlipped(false)
{
}

Rectangle::Rectangle(const int & l, const int & t, const int & w, const int & h)
	: left(l), top(t), width(w), height(h), _isFlipped(false)
{
}

int Rectangle::getRight() const
{
	return left + width;
}

int Rectangle::getBottom() const
{
	return top + height;
}

int Rectangle::getArea() const
{
	return width * height;
}

int Rectangle::getPerimeter() const
{
	return 2 * width + 2 * height;
}

void Rectangle::flip()
{
	_isFlipped = !_isFlipped;

	width ^= height;
	height ^= width;
	width ^= height;
}

bool Rectangle::isFlipped() const
{
	return _isFlipped;
}

void Rectangle::setFlipped(const bool &value)
{
	_isFlipped = value;
}

FitsResult Rectangle::fits(const Rectangle & other, bool allowFlip) const
{
	if (width == other.width && height == other.height) return FitsResult::Perfect;
	if (allowFlip && height == other.width && width == other.height) return FitsResult::PerfectFlipped;
	if (width <= other.width && height <= other.height) return FitsResult::Yes;
	if (allowFlip && height <= other.width && width <= other.height) return FitsResult::Flipped;

	return FitsResult::No;
}

Rectangle Rectangle::create(const int & left, const int & top, const int & right, const int & bottom)
{
	return Rectangle(left, top, right - left, bottom - top);
}
