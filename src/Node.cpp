#include "Node.h"
#include "FitsResult.h"

Node::Node()
	: left(nullptr), right(nullptr), bounds(), isFilled(false)
{
}

Node::~Node()
{
	if (left != nullptr)
	{
		delete left;
		delete right;
	}
}

//http://blackpawn.com/texts/lightmaps/default.html
Node * Node::insert(TextureInfo & textureInfo, const bool & allowFlip)
{
	if (left != nullptr)
	{
		auto node = left->insert(textureInfo, allowFlip);

		if (node != nullptr) return node;

		return right->insert(textureInfo, allowFlip);
	}

	if (isFilled) return nullptr;

	auto result = textureInfo.rectangle.fits(bounds, allowFlip);

	switch (result)
	{
	case Flipped:
		textureInfo.rectangle.flip();
	case Yes:
		break;

	case PerfectFlipped:
		textureInfo.rectangle.flip();
	case Perfect:
		textureInfo.rectangle.left = bounds.left;
		textureInfo.rectangle.top = bounds.top;
		isFilled = true;
		return this;

	case No:
	default:
		return nullptr;
	}

	left = new Node();
	right = new Node();

	auto textureWidth = textureInfo.rectangle.width;
	auto textureHeight = textureInfo.rectangle.height;

	if (bounds.width - textureWidth > bounds.height - textureHeight)
	{
		left->bounds = Rectangle::create(bounds.left, bounds.top, bounds.left + textureWidth, bounds.getBottom());
		right->bounds = Rectangle::create(bounds.left + textureWidth, bounds.top, bounds.getRight(), bounds.getBottom());
	}
	else
	{
		left->bounds = Rectangle::create(bounds.left, bounds.top, bounds.getRight(), bounds.top + textureHeight);
		right->bounds = Rectangle::create(bounds.left, bounds.top + textureHeight, bounds.getRight(), bounds.getBottom());
	}

	return left->insert(textureInfo, allowFlip);
}

void Node::reset()
{
	if (left != nullptr)
	{
		delete left;
		delete right;
		left = nullptr;
		right = nullptr;
	}

	isFilled = false;
	bounds = Rectangle();
}