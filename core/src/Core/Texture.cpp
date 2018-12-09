#include "TXPK/Core/Texture.hpp"

namespace txpk
{
	Texture::Texture()
	{
		path = std::string();
		bounds = NULL;
		offsetX = 0;
		offsetY = 0;
		sourceWidth = 0;
		sourceHeight = 0;
		raw = std::vector<Color4>();
	}

	Texture::Texture(const Texture& other)
	{
		path = other.path;
		bounds = other.bounds;
		offsetX = other.offsetX;
		offsetY = other.offsetY;
		sourceWidth = other.sourceWidth;
		sourceHeight = other.sourceHeight;
		raw = other.raw;
	}

	bool Texture::loadFromFile(const std::string& path)
	{
		int32 width, height, channels;
		uint8* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		
		if (data == NULL)
		{
			stbi_image_free(data);
			return false;
		}

		const uint32 size = static_cast<uint32>(width) * static_cast<uint32>(height);
		raw.resize(0);
		raw.resize(size);

		switch (channels)
		{
		case 4:
			memcpy(&raw[0], data, sizeof(Color4) * size);
			break;
		case 3:
			for (uint32 i = 0; i < size; ++i)
			{
				raw[i].data[0] = data[i * 3];
				raw[i].data[1] = data[i * 3 + 1];
				raw[i].data[2] = data[i * 3 + 2];
				raw[i].data[3] = 0xff;
			}
		}

		this->sourceWidth = static_cast<uint32>(width);
		this->sourceHeight = static_cast<uint32>(height);
		this->bounds = std::make_shared<Rectangle>(Rectangle(this->sourceWidth, this->sourceHeight));
		this->path = get_file_name(path);

		stbi_image_free(data);

		return true;
	}

	bool Texture::loadFromMemory(const Color4* data, uint32 width, uint32 height)
	{
		const uint32 size = width * height;
		raw.resize(0);
		raw.resize(size);

		memcpy(&raw[0], data, sizeof(Color4) * size);
		
		this->sourceWidth = width;
		this->sourceHeight = height;
		this->bounds = std::make_shared<Rectangle>(Rectangle(width, height));
		this->path = std::string();

		return true;
	}

	bool Texture::save(const std::string& path)
	{
		int32 status = 0;

		if (ends_with(path.c_str(), ".png"))
		{
			status = stbi_write_png(path.c_str(), static_cast<int32>(bounds->width), static_cast<int32>(bounds->height), 4, &raw[0], 0);
		}
		else if (ends_with(path.c_str(), ".jpg") || ends_with(path.c_str(), ".jpeg"))
		{
			status = stbi_write_jpg(path.c_str(), static_cast<int32>(bounds->width), static_cast<int32>(bounds->height), 4, &raw[0], 100);
		}

		return status != 0;
	}

	void Texture::trim()
	{
		Margin margin;
		bool colorFound = false;
		
		//iterating top row
		for (uint32 y = 0; y < bounds->height && !colorFound; ++y)
		{
			for (uint32 x = 0; x < bounds->width && !colorFound; ++x)
			{
				if (raw[y * bounds->width + x].data[3] != 0)
					colorFound = true;
			}

			if (colorFound == false)
				margin.top++;
		}

		//iterating left columns
		colorFound = false;
		for (uint32 x = 0; x < bounds->width && !colorFound; ++x)
		{
			for (uint32 y = 0; y < bounds->height && !colorFound; ++y)
			{
				if (raw[y * bounds->width + x].data[3] != 0)
					colorFound = true;
			}

			if (colorFound == false)
				margin.left++;
		}

		//iterating bottom rows
		colorFound = false;
		for (uint32 y = bounds->height - 1; y > 0 && !colorFound; --y)
		{
			for (uint32 x = 0; x < bounds->width && !colorFound; ++x)
			{
				if (raw[y * bounds->width + x].data[3] != 0)
					colorFound = true;
			}

			if (colorFound == false)
				margin.bottom++;
		}

		//iterating right columns
		colorFound = false;
		for (uint32 x = bounds->width - 1; x > 0 && !colorFound; --x)
		{
			for (uint32 y = 0; y < bounds->height && !colorFound; ++y)
			{
				if (raw[y * bounds->width + x].data[3] != 0)
					colorFound = true;
			}

			if (colorFound == false)
				margin.right++;
		}

		/*
		 leftOffset  rightOffset
		     |         |
		   _______________ 
		  |   _________	  | __ topOffset
		  |  |xxxxxxxxx|  |
		  |  |xxxxxxxxx|  |
		  |	 |xxxxxxxxx|  |
		  |	 |xxxxxxxxx|  | __ bottomOffset
		  |_______________|
		
		*/

		this->bounds->width = sourceWidth - margin.left - margin.right;
		this->bounds->height = sourceHeight - margin.top - margin.bottom;
		this->offsetX = margin.left;
		this->offsetY = margin.top;

		raw = apply_margin(raw, sourceWidth, sourceHeight, margin);
	}

	void Texture::adjustRotation()
	{
		//let's play some tetris
		//https://github.com/Seng3694/Tetris/blob/master/engine/src/tetromino.c#L117

		if (bounds->isRotated())
		{
			/*
			assume this texture

			0 1 2 3 4 5
			6 7 8 9 A B
			C D E F G H

			layed out in memory like this  0 1 2 3 4 5 6 7 8 9 A B C D E F G H
			has to be transformed to this (90deg ccw)

			5 B H
			4 A G
			3 9 F
			2 8 E
			1 7 D
			0 6 C

			layed out in memory like this 5 B H 4 A G 3 9 F 2 8 E 1 7 D 0 6 C
			a simple memcpy won't be enough. values can't even be swapped. so we need a copy

			array has still the same size, so no resizing required
			*/

			std::vector<Color4> copy(raw.begin(), raw.end());

			for (uint32 y = 0; y < bounds->width; ++y)
			{
				for (uint32 x = 0; x < bounds->height; ++x)
				{
					raw[(bounds->height - x - 1) * bounds->width + y] = copy[(y * bounds->height) + x];
				}
			}
		}
	}

	bool Texture::operator ==(const Texture& other) const
	{
		if (this->bounds->width != other.bounds->width
			|| this->bounds->height != other.bounds->height)
			return false;

		return array_equals(&this->raw[0], &other.raw[0], static_cast<uint32>(this->raw.size()));
	}

	bool Texture::operator !=(const Texture& other) const
	{
		return !(*this == other);
	}
}
