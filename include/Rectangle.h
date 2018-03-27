#pragma once

#include "FitsResult.h"

struct Rectangle
{
public:
	Rectangle();
	Rectangle(const int &width, const int &height);
	Rectangle(const int &left, const int &top, const int &width, const int &height);

	int left;
	int top;
	int width;
	int height;

	int getRight() const;
	int getBottom() const;
	int getArea() const;
	int getPerimeter() const;

	void flip();
	bool isFlipped() const;
	void setFlipped(const bool &value);

	FitsResult fits(const Rectangle& other, bool allowFlip) const;

	static Rectangle create(const int &left, const int &top, const int &right, const int &bottom);

private:
	bool _isFlipped;
};