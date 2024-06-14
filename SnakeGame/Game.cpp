#include "Game.h"
#include <vector>


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
		UpdateSnakeState(game.snake);

		//-------------------------------------------------------------------------------- Data to use Collider function with tail 
		Rectangle headCollider = GetSnakeHeadCollider(game.snake);
		Rectangle appleCollider = GetAppleCollider(game.apple);
		std::vector<Rectangle> tailColliders = GetSnakeTailCollider(game.snake);
		//--------------------------------------------------------------------------------

		if (DoShapesCollide(headCollider, appleCollider))
		{
			game.snake.tail.push_back(game.snake.tailSegment);
			SetRandomPositionForApple(game.apple);
			UpdateSnakeTail(game.snake); // Need to update snake tail here as well. Otherwise new tail segment spawns with coordinates (0,0) for one frame.
		}
		
		for (const auto& tailCollider : tailColliders)
		{
			if (DoShapesCollide(headCollider, tailCollider))
			{
				window.close();
				break;
			}
		}

		if (DidSnakeCollideWithWall(game.snake))
		{
			window.close();
		}
	}
	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		DrawSnake(game.snake, window);
		DrawApple(game.apple, window);
	}
}












