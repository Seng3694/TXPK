#include "Animation.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

bool Animation::load(const std::string &path)
{
	std::ifstream stream(path);
	
	if (stream.is_open())
	{
		nlohmann::json data;
		stream >> data;

		key = data.at("key").get<std::string>();
		
		for (auto &f : data.at("frames").get<std::vector<nlohmann::json>>())
		{
			auto dur = f.at("duration").get<seconds>();
			frames.push_back({ f.at("id").get<int>(), dur });
			_total += dur;
		}

		stream.close();
		return true;
	}
	else
	{
		return false;
	}
}

void Animation::loadSprites(const Atlas &atlas)
{
	for (auto &f : frames)
	{
		std::stringstream ss;
		ss << key << f.id << ".png";

		for (auto &texture : atlas.textures)
		{
			if (texture.path == ss.str())
			{
				sf::Sprite spr(atlas.texture);
				spr.setTextureRect({ texture.x, texture.y, texture.w, texture.h });
				
				if (texture.flip == true)
				{
					spr.setOrigin(texture.h, 0);
					spr.setRotation(-90);
				}

				_sprites.push_back(spr);

				break;
			}
		}
	}
}

std::shared_ptr<sf::Sprite> Animation::getSprite(const unsigned int& index) const
{
	if (_sprites.size() >= index)
	{
		return std::make_shared<sf::Sprite>(_sprites[index]);
	}

	return nullptr;
}

const seconds Animation::getTotal() const
{
	return _total;
}