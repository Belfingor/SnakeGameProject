#include "Apple.h"

namespace SnakeGame
{
	void InitApple(Apple& apple)
	{
		SetRandomPositionForApple(apple);

		//Init Apple Shape
		apple.appleShape.setSize(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
		apple.appleShape.setFillColor(sf::Color::Red);
		apple.appleShape.setOrigin(SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f);

	}

	void SetRandomPositionForApple(Apple& apple)
	{
		//Init Apple position on screen
		apple.x = (rand() % GRID_CELLS_HORIZONTAL * GRID_SELL_SIZE) + GRID_SELL_SIZE / 2;
		apple.y = (rand() % GRID_CELLS_VERTICAL * GRID_SELL_SIZE) + GRID_SELL_SIZE / 2;

		apple.appleShape.setPosition(apple.x, apple.y);
	}
}


