#include "GameStatePlaying.h"
#include <vector>
#include <cassert>
#include "Game.h"


namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		assert(data.tileSetTexture.loadFromFile("Resources/SnakeTileSet.png"));
		assert(data.font.loadFromFile("Resources/Fonts/Roboto-BlackItalic.ttf"));

		data.snake.snakeHeadSprite.setTexture(data.tileSetTexture);
		data.snake.tailSegment.snakeTailSprite.setTexture(data.tileSetTexture);
		data.apple.appleSprite.setTexture(data.tileSetTexture);

		data.ScoreCountText.setFont(data.font);
		data.ScoreCountText.setCharacterSize(24);
		data.ScoreCountText.setFillColor(sf::Color::White);
		data.ScoreCountText.setPosition(SCREEN_WIDTH / 2.f - 24.f, 6.f);

		//InitGrid(game);
		data.numApplesEaten = 0;
		data.grid.InitGrid();
		InitSnake(data.snake);
		InitApple(data.apple);

		game.isGameWon = false;
	}
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime)
	{
		HandleInput(data.snake);
		UpdateSnakeState(data.snake);

		// Data to use Colliders
		Rectangle headCollider = GetSnakeHeadCollider(data.snake);
		Rectangle appleCollider = GetAppleCollider(data.apple);
		Rectangle screenCollider = GetScreenColloder(); //if screen collision does not work, investigate this function here
		std::vector<Rectangle> tailColliders = GetSnakeTailCollider(data.snake);

		if (DoShapesCollide(headCollider, appleCollider))
		{
			RespawnAppleInAvailableCell(data);
			data.snake.tail.push_back(data.snake.tailSegment);
			UpdateSnakeTail(data.snake); // Need to update snake tail here as well. Otherwise new tail segment spawns with coordinates (0,0) for one frame.
			++data.numApplesEaten;
		}

		for (const auto& tailCollider : tailColliders)
		{
			if (DoShapesCollide(headCollider, tailCollider))
			{
				PushGameState(game, GameStateType::GameOver, false);
				break;
			}
		}

		if (!DoShapesCollide(headCollider, screenCollider))
		{
			PushGameState(game, GameStateType::GameOver, false);
		}

		data.ScoreCountText.setString("Score: " + std::to_string(data.numApplesEaten));

		if (data.snake.tail.size() + 1 == 10) // 10 for testing now, will be == to total num of cell in final
		{
			game.isGameWon = true;
		}
	}

	void RespawnAppleInAvailableCell(GameStatePlayingData& data)
	{
		MarkUnavailableCells(data);
		data.grid.GetAvailableCells();
		data.apple.position = data.grid.GetRandomAvailableCell();
		data.apple.position.x = data.apple.position.x * TILE_SIZE + TILE_SIZE / 2;
		data.apple.position.y = data.apple.position.y * TILE_SIZE + TILE_SIZE / 2;
	}

	void MarkUnavailableCells(GameStatePlayingData& data)
	{
		for (int i = 1; i < GRID_CELLS_HORIZONTAL; ++i)
		{
			for (int j = 0; j < GRID_CELLS_VERTICAL; ++j)
			{
				if (data.snake.position == data.grid.GetCellCoordinatesOnScreen(i, j))
				{
					data.grid.cell[i][j].isAvailable = false;
				}
				for (const auto& segment : data.snake.tail)
				{
					if (segment.position == data.grid.GetCellCoordinatesOnScreen(i, j))
					{
						data.grid.cell[i][j].isAvailable = false;
					}
				}
			}
		}
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, false);
			}
		}
		if (data.isFirstFrameOfPlayingState)
		{
			sf::sleep(sf::seconds(2));
		}
		data.isFirstFrameOfPlayingState = false;
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		DrawSnake(data.snake, window);
		DrawApple(data.apple, window);
		window.draw(data.ScoreCountText);
		
	}
	void ShutDownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		data.isFirstFrameOfPlayingState = true;
		//nothing to deinit here yet
	}
}
