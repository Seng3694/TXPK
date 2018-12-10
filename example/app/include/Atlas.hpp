#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <TXPK/FileSystem/FileSystem.hpp>

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "Texture.hpp"
#include "CustomSprite.hpp"

class Atlas
{
public:
	bool load(const std::string& path);

	CustomSprite getSprite(int id) const;

private:
	sf::Texture texture;
	std::unordered_map<int, Texture> subTextures;
};
