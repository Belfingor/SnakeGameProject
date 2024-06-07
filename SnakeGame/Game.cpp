#include "Game.h"
#include <SFML/Graphics.hpp>


namespace SnakeGame
{
	void InitGrid(Grid& grid) //will use this grid later for apple spawn, but now it is just for visualisation
	{
		for (int i = 0; i < GRID_CELLS_HORIZONTAL; ++i)
		{
			for (int j = 0; j < GRID_CELLS_VERTICAL; ++j)
			{
				grid.cell[i][j].x = i * (SCREEN_WIDTH / GRID_CELLS_HORIZONTAL); //X coordinate of cell on screen
				grid.cell[i][j].y = i * (SCREEN_HEIGHT / GRID_CELLS_VERTICAL); //Y coordinate of cell on screen
			}
		}
	}
	void InitGame(Game& game)
	{
		InitGrid(game.grid);
		InitSnake(game.snake);
		InitApple(game.apple);

		game.tileSetTexture.loadFromFile("Resources/SnakeTileSet.png");
		game.snake.snakeHeadSprite.setTexture(game.tileSetTexture);
		game.snake.tailSegment.snakeTailSprite.setTexture(game.tileSetTexture);
		game.apple.appleSprite.setTexture(game.tileSetTexture);
	
	}
	void UpdateGame(Game& game, sf::RenderWindow& window)
	{
		HandleInput(game.snake);
		UpdateSnakeState(game.snake, game.apple);

		//check for border collision
		if (DidSnakeCollideWithWall(game.snake))
		{
			window.close();
		}

		if (DidSnakeCollideWithTail(game.snake))
		{
			window.close();
		}

		//check if apple is eaten
		if (DidSnakeCollideWithApple(game.snake, game.apple))
		{
			SetRandomPositionForApple(game.apple);
		}
	}
	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		DrawSnake(game.snake, window);
		DrawApple(game.apple, window);
	}
}












// here we gonna return TRUE only if snake's head is fully in cell               //GONNA TRY WITHOUT IT
//bool DoSnakeAndCellCoordinatesMatch(Snake& snake)             
//{
//	return (static_cast<int>(snake.snakeX) % (SCREEN_WIDTH / GRID_CELLS_HORIZONTAL) - GRID_SELL_SIZE / 2== 0) //use static_cast to convert float to int
//		&& (static_cast<int>(snake.snakeY) % (SCREEN_HEIGHT / GRID_CELLS_VERTICAL) - GRID_SELL_SIZE/2 == 0);
//}