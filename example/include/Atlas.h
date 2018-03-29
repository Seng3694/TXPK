#pragma once

#include <string>
#include <vector>

#include "Texture.h"

class Atlas
{
public:
	std::string path;
	std::vector<Texture> textures;
	sf::Texture texture;

	bool load(const std::string &path);
};