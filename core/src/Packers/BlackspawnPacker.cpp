#include "TXPK/Packers/BlackspawnPacker.hpp"

namespace txpk
{
	Bin BlackspawnPacker::pack(RectanglePtrs& rectangles, const uint32& sizeConstraint, const SizeContraintType& constraintType, const bool& allowRotation) const
	{
		Bin bin(rectangles);

		if (rectangles.size() == 1)
		{
			bin.width = rectangles[0]->width;
			bin.height = rectangles[0]->height;
			return bin;
		}

		std::sort(bin.rectangles.begin(), bin.rectangles.end(), [](const RectanglePtr lhs, const RectanglePtr rhs)
		{
			return lhs->getArea() > rhs->getArea();
		});

		uint64 wholeArea = 0;
		for (uint32 i = 0; i < bin.rectangles.size(); ++i)
			wholeArea += bin.rectangles[i]->getArea();

		switch (constraintType)	
		{
		case SizeContraintType::None:
			bin.width = static_cast<uint32>(sqrt(wholeArea));
			bin.height = bin.width;
			break;
		case SizeContraintType::Width:
			bin.width = sizeConstraint;
			bin.height = static_cast<uint32>(wholeArea / sizeConstraint);
			break;
		case SizeContraintType::Height:
			bin.height = sizeConstraint;
			bin.width = static_cast<uint32>(wholeArea / sizeConstraint);
			break;
		}

		Node root;
		root.bounds = Rectangle(bin.width, bin.height);
		bool result = false;

		while (!result)
		{
			for (uint32 i = 0; i < bin.rectangles.size(); ++i)
			{
				result = root.insert(bin.rectangles[i], allowRotation);

				if (!result)
				{
					root.reset();

					switch (constraintType)
					{
					case SizeContraintType::Width:
						bin.height++;
						break;
					case SizeContraintType::Height:
						bin.width++;
						break;
					case SizeContraintType::None:
						bin.width++;
						bin.height++;
						break;
					}

					root.bounds.width = bin.width;
					root.bounds.height = bin.height;

					for (uint32 k = 0; k < bin.rectangles.size(); ++k)
					{
						//reset all positions and flipping
						if (bin.rectangles[k]->isRotated())
							bin.rectangles[k]->rotate();

						bin.rectangles[k]->left = 0;
						bin.rectangles[k]->top = 0;
					} 

					break;
				}
			}
		}

		bool isAnyFlipped = false;
		for (txpk::uint32 i = 0; i < bin.rectangles.size(); ++i)
			if (bin.rectangles[i]->isRotated())
				isAnyFlipped = true;

		return bin;
	}

	BlackspawnPacker::Node::Node()
	{
		left = NULL;
		right = NULL;
		bounds = Rectangle();
		isFilled = false;
	}

	bool BlackspawnPacker::Node::insert(RectanglePtr rect, const bool& allowRotation)
	{
		if (left)
			return left->insert(rect, allowRotation) ? true : right->insert(rect, allowRotation);

		if (isFilled)
			return false;

		FitResult result = rect->fits(bounds, allowRotation);

		switch (result)
		{
		case FitResult::Rotated:
			rect->rotate();
		case FitResult::Yes:
			break;

		case FitResult::PerfectRotated:
			rect->rotate();
		case FitResult::Perfect:
			rect->left = bounds.left;
			rect->top = bounds.top;
			isFilled = true;
			return true;

		case FitResult::No:
		default:
			return false;
		}

		//if it fits but there is still space
		left = std::make_unique<Node>();
		right = std::make_unique<Node>();

		uint32 textureWidth = rect->width;
		uint32 textureHeight = rect->height;

		if (bounds.width - textureWidth > bounds.height - textureHeight)
		{
			left->bounds = Rectangle(bounds.left, bounds.top, bounds.left + textureWidth, bounds.getBottom());
			right->bounds = Rectangle(bounds.left + textureWidth, bounds.top, bounds.getRight(), bounds.getBottom());
		}
		else
		{
			left->bounds = Rectangle(bounds.left, bounds.top, bounds.getRight(), bounds.top + textureHeight);
			right->bounds = Rectangle(bounds.left, bounds.top + textureHeight, bounds.getRight(), bounds.getBottom());
		}

		return left->insert(rect, allowRotation);
	}

	void BlackspawnPacker::Node::reset()
	{
		if (left)
		{
			left->reset();
			right->reset();
			left.reset();
			right.reset();
			left = NULL;
			right = NULL;
		}

		isFilled = false;
		bounds = Rectangle();
	}
}
