#pragma once

#include <string>

#include <SFML/Graphics.hpp>

struct Texture
{
	std::string path;
	int x;
	int y;
	int w;
	int h;
	bool flip;
};