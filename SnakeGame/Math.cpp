#include "Math.h"

namespace SnakeGame 
{
	bool DidSnakeCollideWithWall(Snake& snake)
	{
		return (snake.snakeX + SNAKE_SIZE / 2 > SCREEN_WIDTH || snake.snakeX - SNAKE_SIZE / 2 < 0 ||
			snake.snakeY + SNAKE_SIZE / 2 > SCREEN_HEIGHT || snake.snakeY - SNAKE_SIZE / 2 < 0);
	}

	bool DidSnakeCollideWithApple(Snake& snake, Apple& apple)
	{
		return (snake.snakeX == apple.x && snake.snakeY == apple.y);
	}

	bool DidSnakeCollideWithTail(Snake& snake)
	{
		for (const auto& segment : snake.tail)
		{
			if (snake.snakeX == segment.tailX && snake.snakeY == segment.tailY)
			{
				return true;
			}
		}
		return false;
	}

	// here we gonna return TRUE only if snake's head is fully in cell
	bool DoSnakeAndCellCoordinatesMatch(Snake& snake)
	{
		return (static_cast<int>(snake.snakeX) % (SCREEN_WIDTH / GRID_CELLS_HORIZONTAL) - GRID_SELL_SIZE / 2 == 0) //use static_cast to convert float to int
			&& (static_cast<int>(snake.snakeY) % (SCREEN_HEIGHT / GRID_CELLS_VERTICAL) - GRID_SELL_SIZE / 2 == 0);
	}
	

}
