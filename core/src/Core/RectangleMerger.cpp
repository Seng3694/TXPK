#include "TXPK/Core/RectangleMerger.hpp"

namespace txpk
{
	RectanglePtrs merge_rectangles(TexturePtrs& textures)
	{
		std::set<uint32> indexesToIgnore;
		RectanglePtrs rectangles;
		const uint32 count = static_cast<uint32>(textures.size());

		for (uint32 i = 0; i < count; ++i)
		{
			if (indexesToIgnore.find(i) == indexesToIgnore.end())
			{
				rectangles.push_back(textures[i]->getBounds());
				for (uint32 j = i + 1; j < count; ++j)
				{
					if (indexesToIgnore.find(i) == indexesToIgnore.end())
					{
						if (*textures[i] == *textures[j])
						{
							indexesToIgnore.insert(j);
							textures[j]->setBounds(textures[i]->getBounds());
						}
					}
				}
			}
		}

		return rectangles;
	}
}
