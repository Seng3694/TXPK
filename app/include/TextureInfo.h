#pragma once

#include <string>

#include "Rectangle.h"

struct TextureInfo
{
public: 
	Rectangle rectangle;
	std::string path;

	friend std::ostream& operator<<(std::ostream& stream, const TextureInfo& info);
};