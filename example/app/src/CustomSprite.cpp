#include "CustomSprite.hpp"

CustomSprite::CustomSprite()
{
	width = 0;
	height = 0;
	innerSprite = sf::Sprite();
}

void CustomSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(innerSprite, states);
}

unsigned int CustomSprite::getWidth() const
{
	return width;
}

unsigned int CustomSprite::getHeight() const
{
	return height;
}

sf::Vector2f CustomSprite::getSize() const
{
	return sf::Vector2f(static_cast<float>(width), static_cast<float>(height));
}