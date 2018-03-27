#include "ImageRenderer.h"

sf::Image ImageRenderer::draw(const Bin& bin, const std::unordered_map<std::string, sf::Texture>& textures, const sf::Color& clearColor)
{
	sf::RenderTexture texture;
	texture.create(bin.width, bin.heigth);

	texture.clear(clearColor);

	for (auto &info : bin.infos)
	{
		auto sprite = sf::Sprite(textures.find(info->path)->second);

		if (info->rectangle.isFlipped())
		{
			sprite.setRotation(90);
			sprite.setOrigin(0, info->rectangle.width);
		}

		sprite.setPosition(info->rectangle.left, info->rectangle.top);
		texture.draw(sprite);
	}
	
	texture.display();
	
	return texture.getTexture().copyToImage();
}