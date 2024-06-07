#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace SnakeGame
{
	struct Apple
	{
		float x = 0;
		float y = 0;
		sf::Sprite appleSprite;
	};


	void InitApple(Apple& apple);
	void SetRandomPositionForApple(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}