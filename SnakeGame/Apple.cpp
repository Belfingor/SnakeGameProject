#include "Apple.h"

namespace SnakeGame
{
	void InitApple(Apple& apple)
	{
		SetRandomPositionForApple(apple);

		//Init Apple Sprite
		apple.appleSprite.setTextureRect(sf::IntRect(48, 0, 8, 8));
		apple.appleSprite.setScale(5, 5);
		apple.appleSprite.setOrigin(SNAKE_SIZE / 10.f, SNAKE_SIZE / 10.f);

	}

	void SetRandomPositionForApple(Apple& apple)
	{
		//Init Apple position on screen
		apple.x = (rand() % GRID_CELLS_HORIZONTAL * GRID_SELL_SIZE) + GRID_SELL_SIZE / 2;
		apple.y = (rand() % GRID_CELLS_VERTICAL * GRID_SELL_SIZE) + GRID_SELL_SIZE / 2;
	}
	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.appleSprite.setPosition(apple.x, apple.y);
		window.draw(apple.appleSprite);
	}
}


