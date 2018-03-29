#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Frame.h"
#include "Atlas.h"

class Animation
{
public:
	std::string key;
	std::vector<Frame> frames;

	const seconds getTotal() const;
	bool load(const std::string& path);
	void loadSprites(const Atlas &atlas);
	std::shared_ptr<sf::Sprite> getSprite(const unsigned int& index) const;

private: 
	seconds _total;
	std::vector<sf::Sprite> _sprites;
};