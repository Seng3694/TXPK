#pragma once

#include <string.h>
#include <string>
#include <vector>
#include <list>

#include <stb_image.h>
#include <stb_image_write.h>

#include "TXPK/Core/Color.hpp"
#include "TXPK/Core/Common.hpp"
#include "TXPK/Core/Comparison.hpp"
#include "TXPK/Core/Rectangle.hpp"
#include "TXPK/Core/StringExtension.hpp"
#include "TXPK/Core/VectorExtension.hpp"
#include "TXPK/FileSystem/FileSystem.hpp"

namespace txpk
{
	/**
	* \brief The texture class. Holds raw pixel data and dimension data.
	*/
	class Texture
	{
	public:
		/**
		* \brief The default constructor.
		*/
		Texture();
		/**
		* \brief The copy constructor.
		* \param other Texture to copy.
		*/
		Texture(const Texture& other);

		inline std::string getPath() const; /**< gets the path value */
		inline RectanglePtr getBounds() const; /**< gets the bounds value */
		inline uint32 getOffsetX() const; /**< gets the x offset value */
		inline uint32 getOffsetY() const; /**< gets the y offset value */
		inline uint32 getSourceWidth() const; /**< gets the source width value */
		inline uint32 getSourceHeight() const; /**< gets the source height value */
		inline std::vector<Color4> getRawPixelData() const; /**< gets the raw pixel data */

		inline void setOffsetX(uint32 offset); /**< sets the x offset value */
		inline void setOffsetY(uint32 offset); /**< sets the y offset value */
		inline void setBounds(RectanglePtr rectangle); /**< sets the bounds value */

		/**
		* \brief Loads a texture from the filesystem.
		* \param path The path to the file to load.
		* \return Returns whether loading the file was successful or not.
		*/
		bool loadFromFile(const std::string& path);
		/**
		* \brief Loads raw pixel data into a texture.
		* \param data The actual pixel data.
		* \param width The width of the resulting texture.
		* \param height The height of the resulting texture.
		* \return Returns whether loading from memory was successful or not.
		*/
		bool loadFromMemory(const Color4* data, uint32 width, uint32 height);
		/**
		* \brief Saves the texture data as an image to the path.
		* \param path Path including filename and extension. Currently .png and .jpg/.jpeg are supported.
		* \return Returns whether saving the texture at the given path was successful or not.
		*/
		bool save(const std::string& path);

		/**
		* \brief Trims the texture and removes any excess transparency at the borders.
		*/
		void trim();
		/**
		* \brief Rotates the texture 90° ccw if the rectangle bounds was rotated.
		* This method is used to adjust textures which rectangles got rotated while being packed.
		*/
		void adjustRotation();
		
		bool operator ==(const Texture& other) const; /**< Checks if this texture is equal to the other one */
		bool operator !=(const Texture& other) const; /**< Checks if this texture is unequal to the other one */

	private:
		std::string path; /**< The path where the image got loaded from. Empty if it was loaded from memory */
		uint32 offsetX; /**< The left offset which can be a result of texture trimming */
		uint32 offsetY; /**< The top offset which can be a result of texture trimming */
		uint32 sourceWidth; /**< The width the texture had when loaded (before trimming/rotating) */
		uint32 sourceHeight; /**< The height the texture had when loaded (before trimming/rotating) */
		RectanglePtr bounds; /**< The actual dimension of the texture. This pointer can be shared between different textures */
		std::vector<Color4> raw; /**< The pixel color data */
	};

	typedef std::shared_ptr<Texture> TexturePtr;
	typedef std::vector<TexturePtr> TexturePtrs;
}

#include "TXPK/Core/Texture.inl"
