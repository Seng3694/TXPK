#include <json.hpp>
#include <fstream>
#include <iostream>
#include "Atlas.h"
#include "Texture.h"
#include "Animation.h"
#include "Frame.h"
#include "AnimatedSprite.h"
#include <SFML/System.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(560, 320), "packer test", sf::Style::Default, sf::ContextSettings(0, 0, 8));

	sf::Font font{};
	font.loadFromFile("content/fonts/arcadeclassis.ttf");

	sf::Text text{};
	text.setFont(font);
	text.setString("Dying                   Hit                     Attack");
	text.setPosition(50, 10);
	text.setFillColor(sf::Color::Black);

	Atlas skeletonAtlas{};
	skeletonAtlas.load("content/meta/atlas.json");

	Animation skeletonDeadAnimation{};
	skeletonDeadAnimation.load("content/animations/skeleton_dead.json");
	skeletonDeadAnimation.loadSprites(skeletonAtlas);

	Animation skeletonHitAnimation{};
	skeletonHitAnimation.load("content/animations/skeleton_hit.json"); //contains rotated textures
	skeletonHitAnimation.loadSprites(skeletonAtlas);

	Animation skeletonAttackAnimation{};
	skeletonAttackAnimation.load("content/animations/skeleton_attack.json");
	skeletonAttackAnimation.loadSprites(skeletonAtlas);

	AnimatedSprite skeletonSprite1{};
	skeletonSprite1.setScale(5, 5);
	skeletonSprite1.setPosition(10, 64);
	skeletonSprite1.addAnimation("dead", skeletonDeadAnimation);
	skeletonSprite1.playAnimation("dead", true);
	
	AnimatedSprite skeletonSprite2{};
	skeletonSprite2.setScale(5, 5);
	skeletonSprite2.setPosition(170, 64);
	skeletonSprite2.addAnimation("hit", skeletonHitAnimation);
	skeletonSprite2.playAnimation("hit", true);

	AnimatedSprite skeletonSprite3{};
	skeletonSprite3.setScale(5, 5);
	skeletonSprite3.setPosition(330, 64);
	skeletonSprite3.setOrigin(0, 5);
	skeletonSprite3.addAnimation("attack", skeletonAttackAnimation);
	skeletonSprite3.playAnimation("attack", true);

	sf::Clock c{};
	
	while (window.isOpen())
	{
		auto elapsed = c.restart().asSeconds();

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::EventType::Closed)
				window.close();
		}

		skeletonSprite1.update(elapsed);
		skeletonSprite2.update(elapsed);
		skeletonSprite3.update(elapsed);

		window.clear(sf::Color(0xAD9B89FF));

		skeletonSprite1.draw(window, sf::RenderStates::Default);
		skeletonSprite2.draw(window, sf::RenderStates::Default);
		skeletonSprite3.draw(window, sf::RenderStates::Default);

		window.draw(text);

		window.display();
	}

	return 0;
}