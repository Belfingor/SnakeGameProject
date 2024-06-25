#include "Apple.h"
#include "Math.h"


namespace SnakeGame
{
	void InitApple(Apple& apple)
	{
		SetRandomPositionForApple(apple);

		// Init Apple Sprite
		apple.appleSprite.setTextureRect(sf::IntRect(48, 0, 8, 8));
		apple.appleSprite.setScale(5, 5);
		apple.appleSprite.setOrigin(SNAKE_SIZE / 10.f, SNAKE_SIZE / 10.f);
	}

	void SetRandomPositionForApple(Apple& apple)
	{
		// Init Apple position on screen (only when game starts, different function will be used for position change)
		apple.position.x = (rand() % GRID_CELLS_HORIZONTAL * GRID_CELL_SIZE) + GRID_CELL_SIZE / 2;
		apple.position.y = (rand() % GRID_CELLS_VERTICAL * GRID_CELL_SIZE) + GRID_CELL_SIZE / 2;
	}
	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.appleSprite.setPosition(apple.position.x, apple.position.y);
		window.draw(apple.appleSprite);
	}
	Rectangle GetAppleCollider(const Apple& apple)
	{
		return { {apple.position.x - SNAKE_SIZE / 2.f, apple.position.y - SNAKE_SIZE / 2.f},
			{SNAKE_SIZE, SNAKE_SIZE} };
	}
}


