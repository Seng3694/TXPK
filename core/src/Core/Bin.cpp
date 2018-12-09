#include "TXPK/Core/Bin.hpp"

namespace txpk
{
	Bin::Bin(RectanglePtrs rectangles)
	{
		this->rectangles = rectangles;
		this->width = 0;
		this->height = 0;
	}

	bool Bin::save(TexturePtrs& textures, const Color4& clearColor, const std::string& path, const bool& trim)
	{
		const uint32 size = width * height;
		Color4* data = new Color4[size];
		memset(data, 0, size * sizeof(Color4));

		std::vector<Color4> textureData;
		const Rectangle* current = NULL;
		uint32 r, t, y;
		//foreach rectangle
		for (r = 0; r < rectangles.size(); ++r)
		{
			//actually faster than copying a smartpointer...
			current = &(*rectangles[r]);

			//find corresponding texture
			for (t = 0; t < textures.size(); ++t)
			{
				//when addresses match
				if (&(*textures[t]->getBounds()) == &(*current))
				{
					textureData = textures[t]->getRawPixelData();

					//copy data row by row
					for (y = 0; y < current->height; ++y)
					{
						memcpy(
							&data[(current->top + y) * width + current->left],
							&textureData[y * current->width],
							current->width * sizeof(Color4)
						);
					}

					break;
				}
			}
		}

		for (r = 0; r < size; ++r)
		{
			if(data[r].data[3] == 0)
				data[r] = clearColor;
		}

		Texture texture;
		texture.loadFromMemory(data, width, height);

		if(trim)
			texture.trim();

		width = texture.getBounds()->width;
		height = texture.getBounds()->height;

		delete[] data;
		return texture.save(path);
	}
}
