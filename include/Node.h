#pragma once

#include "Rectangle.h"
#include "TextureInfo.h"

struct Node
{
public:
	Node();
	~Node();

	Node * left;
	Node * right;
	Rectangle bounds;
	bool isFilled;

	Node * insert(TextureInfo & textureInfo, const bool & allowFlip);
	void reset();
};