#include "Apple.h"
#include "Math.h"
#include "GameStatePlaying.h"


namespace SnakeGame
{
	void InitApple(Apple& apple)
	{
		// Init Apple Sprite
		apple.appleSprite.setTextureRect(sf::IntRect(48, 0, 8, 8));
		apple.appleSprite.setScale(5, 5);
		apple.appleSprite.setOrigin(SNAKE_SIZE / 10.f, SNAKE_SIZE / 10.f);
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


