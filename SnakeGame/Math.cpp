#include "Math.h"
#include "Snake.h"
#include "Apple.h"

namespace SnakeGame 
{
	bool DoShapesCollide(const Rectangle& rectangle1, const Rectangle& rectangle2)
	{
		return rectangle1.position.x < rectangle2.position.x + rectangle2.size.x &&
			rectangle1.position.x + rectangle1.size.x > rectangle2.position.x &&
			rectangle1.position.y < rectangle2.position.y + rectangle2.size.y &&
			rectangle1.position.y + rectangle1.size.y > rectangle2.position.y;
	}

	bool DidSnakeCollideWithWall(Snake& snake)
	{
		return (snake.position.x + SNAKE_SIZE / 2 > SCREEN_WIDTH || snake.position.x - SNAKE_SIZE / 2 < 0 ||
			snake.position.y + SNAKE_SIZE / 2 > SCREEN_HEIGHT || snake.position.y - SNAKE_SIZE / 2 < 0);
	}

	bool DidSnakeCollideWithTail(Snake& snake)
	{
		for (const auto& segment : snake.tail)
		{
			if (snake.position.x == segment.position.x && snake.position.y == segment.position.y)
			{
				return true;
			}
		}
		return false;
	}
}
