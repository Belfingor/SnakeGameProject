#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Constants.h"

namespace SnakeGame
{
	struct Apple
	{
		float x = 0;
		float y = 0;
		sf::RectangleShape appleShape;
	};


	void InitApple(Apple& apple);
	void SetRandomPositionForApple(Apple& apple);
}