#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Bin.h"

class ImageRenderer
{
public:
	static sf::Image draw(const Bin& bin, const std::unordered_map<std::string, sf::Texture>& textures, const sf::Color& clearColor);
};