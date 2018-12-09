#include "Atlas.hpp"

bool Atlas::load(const std::string& path)
{
	std::ifstream stream(path);

	if (stream.is_open())
	{
		nlohmann::json json;

		try
		{
			stream >> json;
		}
		catch(const nlohmann::json::exception&)
		{
			stream.close();
			return false;
		}

		std::string imgPath = txpk::get_directory(path) + "/" + json.at("meta").at("img").get<std::string>();
		if (!texture.loadFromFile(imgPath))
		{
			stream.close();
			return false;
		}

		for (auto itr = json.at("bin").begin(); itr != json.at("bin").end(); ++itr)
		{
			Texture texture;
			texture.key = itr->at("key").get<int>();
			texture.x = itr->at("x").get<unsigned int>();
			texture.y = itr->at("y").get<unsigned int>();
			texture.width = itr->at("w").get<unsigned int>();
			texture.height = itr->at("h").get<unsigned int>();
			texture.offsetX = itr->at("ox").get<unsigned int>();
			texture.offsetY = itr->at("oy").get<unsigned int>();
			texture.sourceWidth = itr->at("sw").get<unsigned int>();
			texture.sourceHeight = itr->at("sh").get<unsigned int>();
			texture.rotated = itr->at("r").get<bool>();
			subTextures[texture.key] = texture;
		}

		stream.close();
	}
	else
	{
		return false;
	}

	return true;
}

CustomSprite Atlas::getSprite(int id) const
{
	//CustomSprite is a renderable, transformable which encapsulates 
	//another sprite in it to combine transforms before drawing because
	//the inner sprite has to be transformed here and should not be changed
	CustomSprite sprite;

	//subtextures are the texture informations which got loaded from the json file
	auto itr = subTextures.find(id);
	if (itr == subTextures.end())
		return sprite;

	const Texture& subTexture = itr->second;

	//set inner sprites texture to the whole atlas
	sprite.innerSprite.setTexture(texture);
	//set cropping rectangle/quad
	sprite.innerSprite.setTextureRect(sf::IntRect(subTexture.x, subTexture.y, subTexture.width, subTexture.height));

	if (subTexture.rotated)
	{
		//if the texture got rotated we have to rotate it back
		sprite.innerSprite.setRotation(90);
		//and adjust the position
		sprite.innerSprite.move(subTexture.height, 0);
	}

	//adjust the trimming offset
	sprite.innerSprite.move(subTexture.offsetX, subTexture.offsetY);
	
	//the custom sprite implementation holds the width and height so you can center the origin for rotation
	sprite.width = subTexture.sourceWidth;
	sprite.height = subTexture.sourceHeight;

	return sprite;
}