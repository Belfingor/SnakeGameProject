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
		apple.appleSprite.setOrigin(TILE_SIZE / 10.f, TILE_SIZE / 10.f);
	}
	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.appleSprite.setPosition(apple.position.x, apple.position.y);
		window.draw(apple.appleSprite);
	}
	Rectangle GetAppleCollider(const Apple& apple)
	{
		return { {apple.position.x - TILE_SIZE / 2.f, apple.position.y - TILE_SIZE / 2.f},
			{TILE_SIZE, TILE_SIZE} };
	}
}


