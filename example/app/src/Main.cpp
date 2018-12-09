#include <SFML/Graphics.hpp>

#include "Atlas.hpp"
#include "CustomSprite.hpp"
#include "skeleton.hpp"

#define PI 3.14159265359f
#define DEG(x) (x / 2 * PI) * 360
#define RAD(x) (180 * x) / PI

int main()
{
	sf::RenderWindow window(sf::VideoMode(450, 250), "TXPK Usage Example");

	Atlas atlas;
	if (!atlas.load("content/meta/skeleton.json"))
		return 1;

	std::vector<CustomSprite> attackSprites;
	for(unsigned int i = SKELETON_ATTACK_1; i <= SKELETON_ATTACK_18; ++i)
		attackSprites.push_back(atlas.getSprite(i));

	std::vector<CustomSprite> dyingSprites;
	for (unsigned int i = SKELETON_DEAD_1; i <= SKELETON_DEAD_15; ++i)
		dyingSprites.push_back(atlas.getSprite(i));

	sf::Clock clock;
	float dt;

	float attackElapsed = 0;
	const float attackAnimTime = 2;
	const float attackPart = attackAnimTime / attackSprites.size();

	float dyingElapsed = 0;
	const float dyingAnimTime = 1.5f;
	const float dyingPart = dyingAnimTime / dyingSprites.size();

	float rotation = 0;
	float rotationSpeed = 0.1f;

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
			if (e.type == sf::Event::Closed)
				window.close();

		dt = clock.restart().asSeconds();
		attackElapsed += dt;
		dyingElapsed += dt;
		rotation += (rotationSpeed * dt);

		if (attackElapsed >= attackAnimTime)
			attackElapsed = 0;

		if (dyingElapsed >= dyingAnimTime)
			dyingElapsed = 0;

		if (rotation >= 2 * PI)
			rotation = 0;

		sf::RenderStates states;
		states.transform.scale(4, 4);

		window.clear(sf::Color(0xAD9B89FF));

		CustomSprite& currentAttackSprite = attackSprites[attackElapsed / attackPart];
		currentAttackSprite.setPosition(30, 30);
		currentAttackSprite.setOrigin(currentAttackSprite.getWidth() / 2, currentAttackSprite.getHeight() / 2);
		currentAttackSprite.setRotation(DEG(rotation));

		CustomSprite& currentDyingSprite = dyingSprites[dyingElapsed / dyingPart];
		currentDyingSprite.setPosition(85, 30);
		currentDyingSprite.setOrigin(currentDyingSprite.getWidth() / 2, currentDyingSprite.getHeight() / 2);
		currentDyingSprite.setRotation(DEG(rotation));

		sf::RectangleShape rect;
		rect.setSize(currentAttackSprite.getSize());
		rect.setPosition(currentAttackSprite.getPosition());
		rect.setFillColor(sf::Color(0x00000011));
		rect.setOrigin(currentAttackSprite.getOrigin());
		rect.setRotation(DEG(rotation));
		window.draw(rect, states);

		window.draw(currentAttackSprite, states);

		rect.setSize(currentDyingSprite.getSize());
		rect.setPosition(currentDyingSprite.getPosition());
		rect.setFillColor(sf::Color(0x00000011));
		rect.setOrigin(currentDyingSprite.getOrigin());
		window.draw(rect, states);

		window.draw(currentDyingSprite, states);


		window.display();
	}

	return 0;
}