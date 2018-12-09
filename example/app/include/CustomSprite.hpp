#pragma once

#include <SFML/Graphics.hpp>

class Atlas;

class CustomSprite : public sf::Transformable, public sf::Drawable
{
	friend class Atlas;

public:
	CustomSprite();

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	sf::Vector2f getSize() const;

private:
	sf::Sprite innerSprite;
	unsigned int width;
	unsigned int height;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
