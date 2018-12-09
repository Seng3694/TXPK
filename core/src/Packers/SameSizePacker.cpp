#include "TXPK/Packers/SameSizePacker.hpp"

namespace txpk
{
	bool SameSizePacker::validate(RectanglePtrs& rectangles, const uint32& sizeConstraint, const SizeContraintType& constraintType, const bool& allowRotation) const
	{
		for (uint32 i = 0; i < rectangles.size() - 1; ++i)
		{
			if (*rectangles[i] != *rectangles[i + 1])
				return false;
		}

		return true;
	}

	Bin SameSizePacker::pack(RectanglePtrs& rectangles, const uint32& sizeConstraint, const SizeContraintType& constraintType, const bool& allowRotation) const
	{
		Bin bin(rectangles);

		if (rectangles.size() == 1)
		{
			bin.width = rectangles[0]->width;
			bin.height = rectangles[0]->height;
			return bin;
		}

		const uint32 count = static_cast<uint32>(bin.rectangles.size());
		const uint32 textureWidth = bin.rectangles[0]->width;
		const uint32 textureHeight = bin.rectangles[0]->height;
		uint32 i = 0;

		if (constraintType == SizeContraintType::Width)
		{
			bin.width = sizeConstraint;
			bin.height = (count / (bin.width / textureWidth)) * textureHeight;
		}
		else if (constraintType == SizeContraintType::Height)
		{
			bin.height = sizeConstraint;
			bin.width = (count / (bin.height / textureHeight)) * textureWidth;
		}
		else
		{
			if (count < 4)
			{
				//if textureHeight is larger than textureWidth pack them horizontally
				if (textureHeight >= textureWidth)
				{
					bin.width = static_cast<uint32>(bin.rectangles.size()) * textureWidth;
					bin.height = textureHeight;
				}
				//else pack them vertically
				else
				{
					bin.width = textureWidth;
					bin.height = static_cast<uint32>(bin.rectangles.size()) * textureHeight;
				}
			}
			else
			{
				float sqr = sqrt(static_cast<float>(count));
				if (sqr == floor(sqr))
				{
					uint32 size = static_cast<uint32>(sqr);
					bin.width = textureWidth * size;
					bin.height = textureHeight * size;
				}
				else
				{
					uint32 newCount = count;
					while (is_prime(newCount))
						newCount++;

					std::vector<int32> factors = get_two_large_factors(newCount);

					bin.width = textureWidth * static_cast<uint32>(MAX(factors[0], factors[1]));
					bin.height = textureHeight * static_cast<uint32>(MIN(factors[0], factors[1]));
				}
			}
		}

		for (i = 0; i < count; ++i)
		{
			bin.rectangles[i]->left = (i * textureWidth) % bin.width;
			bin.rectangles[i]->top = ((i * textureWidth) / bin.width) * textureHeight;
		}

		return bin;
	}
}
