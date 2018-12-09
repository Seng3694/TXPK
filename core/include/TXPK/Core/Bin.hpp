#pragma once

#include <vector>

#include "TXPK/Core/Color.hpp"
#include "TXPK/Core/Texture.hpp"

namespace txpk
{
	/**
	* \brief A Bin resembles a container with packed images in form of rectangles.
	*/
	class Bin
	{
	public:
		uint32 width; /**< Width of the resulting image */
		uint32 height; /**< Height of the resulting image */
		RectanglePtrs rectangles; /**< Rectangle pointers to manipulate */

		/**
		* \brief Creates a new Bin.
		* \param rectangles List of rectangle pointers.
		*/
		Bin(RectanglePtrs rectangles);

		/**
		* \brief Maps the internal rectangle pointers back to their textures and creates the actual image.
		* \param textures The textures to map the rectangle pointers to.
		* \param clearColor The background color of the resulting image. Default is black transparent.
		* \param path The absolute path where the image should be saved to (including image name and extension).
		* \param trim Whether the resulting image should be trimmed or not. Trimming cuts the spare transparency at the borders.
		* \return Will return true if saving the texture was successful. False if not.
		*/
		bool save(TexturePtrs& textures, const Color4& clearColor, const std::string& path, const bool& trim);
	};
}
