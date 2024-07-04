#pragma once
#include "Math.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"


namespace SnakeGame
{
	struct Apple
	{
		Position2D position;
		sf::Sprite appleSprite;
	};

	void InitApple(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	Rectangle GetAppleCollider(const Apple& apple);
}