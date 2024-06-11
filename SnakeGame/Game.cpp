#include "Game.h"
#include <SFML/Graphics.hpp>


namespace SnakeGame
{
	void InitGrid(Grid& grid) //Grid for game logic to spawn apples on it and determine snake's movement accordingly
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
		game.tileSetTexture.loadFromFile("Resources/SnakeTileSet.png");
		game.snake.snakeHeadSprite.setTexture(game.tileSetTexture);
		game.snake.tailSegment.snakeTailSprite.setTexture(game.tileSetTexture);
		game.apple.appleSprite.setTexture(game.tileSetTexture);

		InitGrid(game.grid);
		InitSnake(game.snake);
		InitApple(game.apple);
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












