#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	: _index(0), _currentAnimation(""), _elapsed(0)
{
}

void AnimatedSprite::update(float dt)
{
	if (_isPlaying)
	{
		auto anim = _animations[_currentAnimation];
		_elapsed += dt;
		
		while (_elapsed >= anim.frames[_index].duration)
		{
			_elapsed -= anim.frames[_index].duration;
			_index = (_index + 1) % anim.frames.size();

			if (_index == 0 && !_isLooped)
			{
				_isPlaying = false;
			}
		}
	}
}

void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states)
{
	auto anim = _animations[_currentAnimation];
	auto sprite = anim.getSprite(_index);
	
	if (sprite)
	{
		states.transform.combine(getTransform());
		target.draw(*sprite, states);
	}

}

void AnimatedSprite::addAnimation(const std::string &key, Animation &animation)
{
	_animations[key] = animation;
}

void AnimatedSprite::playAnimation(const std::string &key, const bool &looped)
{
	auto itr = _animations.find(key);
	if (itr != _animations.end())
	{
		_currentAnimation = key;
		_isLooped = looped;
		_isPlaying = true;
	}
}