#include "Game.h"
#include <vector>


namespace SnakeGame
{
	void InitGame(Game& game)
	{
		game.tileSetTexture.loadFromFile("Resources/SnakeTileSet.png");
		game.snake.snakeHeadSprite.setTexture(game.tileSetTexture);
		game.snake.tailSegment.snakeTailSprite.setTexture(game.tileSetTexture);
		game.apple.appleSprite.setTexture(game.tileSetTexture);

		//InitGrid(game);
		game.grid.InitGrid();
		InitSnake(game.snake);
		InitApple(game.apple);
	}
	void UpdateGame(Game& game, sf::RenderWindow& window)
	{
		HandleInput(game.snake);
		UpdateSnakeState(game.snake);

		//Data to use Collider function with tail 
		Rectangle headCollider = GetSnakeHeadCollider(game.snake);
		Rectangle appleCollider = GetAppleCollider(game.apple);
		std::vector<Rectangle> tailColliders = GetSnakeTailCollider(game.snake);
		

		if (DoShapesCollide(headCollider, appleCollider))
		{
			RespawnAppleInAvailableCell(game);
			game.snake.tail.push_back(game.snake.tailSegment);
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

	void RespawnAppleInAvailableCell(Game& game)
	{
		MarkUnavailableCells(game);
		game.grid.GetAvailableCells();
		game.apple.position = game.grid.GetRandomAvailableCell();
		game.apple.position.x = game.apple.position.x * GRID_CELL_SIZE + 20;
		game.apple.position.y = game.apple.position.y * GRID_CELL_SIZE + 20;
	}

	void MarkUnavailableCells(Game& game)
	{
		for (int i = 1; i < GRID_CELLS_HORIZONTAL; ++i)
		{
			for (int j = 0; j < GRID_CELLS_VERTICAL; ++j)
			{
				if (game.snake.position == game.grid.GetCellCoordinatesOnScreen(i, j))
				{
					game.grid.cell[i][j].isAvailable = false;
				}
				for (const auto& segment : game.snake.tail)
				{
					if (segment.position == game.grid.GetCellCoordinatesOnScreen(i, j))
					{
						game.grid.cell[i][j].isAvailable = false;
					}
				}
			}
		}
	}
}












