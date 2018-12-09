#pragma once

#include <set>
#include <vector>

#include "TXPK/Core/Rectangle.hpp"
#include "TXPK/Core/Texture.hpp"

namespace txpk
{
	/**
	* \brief Extracts and merges all rectangles from textures.
	* If there are equal textures (raw pixel data) the rectangles will be merged to one. 
	* The textures will be adjusted to point to the same rectangle.
	* \param textures The textures to extract the rectangles from.
	*/
	RectanglePtrs merge_rectangles(TexturePtrs& textures);
}
