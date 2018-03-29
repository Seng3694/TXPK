#pragma once

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Animation.h"

class AnimatedSprite : public sf::Transformable
{
public:
	AnimatedSprite();

	void update(float dt);
	void draw(sf::RenderTarget &target, sf::RenderStates states);
	void addAnimation(const std::string &key, Animation &animation);
	void playAnimation(const std::string &key, const bool &looped = true);

private:
	std::unordered_map<std::string, Animation> _animations;
	std::string _currentAnimation;
	bool _isLooped;
	bool _isPlaying;
	float _elapsed;
	unsigned int _index;
};