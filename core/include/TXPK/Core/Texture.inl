#include "TXPK/Core/Texture.hpp"

namespace txpk
{
	std::string Texture::getPath() const
	{
		return path;
	}

	RectanglePtr Texture::getBounds() const
	{
		return bounds;
	}

	uint32 Texture::getOffsetX() const
	{
		return offsetX;
	}

	uint32 Texture::getOffsetY() const
	{
		return offsetY;
	}

	uint32 Texture::getSourceWidth() const
	{
		return sourceWidth;
	}

	uint32 Texture::getSourceHeight() const
	{
		return sourceHeight;
	}

	std::vector<Color4> Texture::getRawPixelData() const
	{
		return raw;
	}

	void Texture::setOffsetX(uint32 offset)
	{
		offsetX = offset;
	}

	void Texture::setOffsetY(uint32 offset)
	{
		offsetY = offset;
	}

	void Texture::setBounds(RectanglePtr rectangle)
	{
		bounds = rectangle;
	}
}
