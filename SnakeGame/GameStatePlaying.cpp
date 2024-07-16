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
		assert(data.snakeHitSoundBuffer.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav"));
		//-------------------------------------------------------------------------------- 

		data.snake.snakeHeadSprite.setTexture(data.tileSetTexture);
		data.snake.tailSegment.snakeTailSprite.setTexture(data.tileSetTexture);
		data.apple.appleSprite.setTexture(data.tileSetTexture);

		data.scoreCountText.setFont(data.font);
		data.scoreCountText.setCharacterSize(24);
		data.scoreCountText.setFillColor(sf::Color::White);
		data.scoreCountText.setPosition(SCREEN_WIDTH / 2.f - 24.f, 6.f);

		data.countdownText.setFont(data.font);
		data.countdownText.setCharacterSize(60);
		data.countdownText.setFillColor(sf::Color::White);
		data.countdownText.setPosition( SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 3);

		data.playingInputClueText.setFont(data.font);
		data.playingInputClueText.setCharacterSize(24);
		data.playingInputClueText.setFillColor(sf::Color::White);
		data.playingInputClueText.setPosition(SCREEN_WIDTH / 2.6, SCREEN_HEIGHT / 5);
		data.playingInputClueText.setString("Use Arrows to Move\n       Esc to Pause");

		data.snakeHitSound.setBuffer(data.snakeHitSoundBuffer);
		data.snakeHitSound.setVolume(50.f);

		//InitGrid(game);
		data.numApplesEaten = 0;
		game.gameScore = 0;
		data.grid.InitGrid();
		MarkWallCellsAsUnavailable(data);
		InitSnake(data.snake);
		InitApple(data.apple);
		SpawnAppleInAvailableCell(data);

		game.isGameWon = false;
		data.timeSinceGameStarted = 0;
		data.snake.deltaTimeToMove = 0;
	}
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime)
	{
		data.timeSinceGameStarted += deltaTime;
		data.snake.deltaTimeToMove += deltaTime;
		
		if (data.timeSinceGameStarted > PAUSE_TIME_IN_SECONDS_BEFORE_GAME_STARTS)
		{
			HandleInput(data.snake);
			if (data.snake.deltaTimeToMove > .25f - game.gameSpeedModifier)
			{
				UpdateSnakePosition(data.snake);
			}
			
			// Data to use Colliders
			Rectangle headCollider = GetSnakeHeadCollider(data.snake);
			Rectangle appleCollider = GetAppleCollider(data.apple);
			Rectangle screenCollider = GetScreenColloder();
			std::vector<Rectangle> tailColliders = GetSnakeTailCollider(data.snake);

			if (DoShapesCollide(headCollider, appleCollider))
			{
				SpawnAppleInAvailableCell(data);
				data.snake.tail.push_back(data.snake.tailSegment);
				UpdateSnakeTail(data.snake); // Need to update snake tail here as well. Otherwise new tail segment spawns with coordinates (0,0) for one frame.
				++data.numApplesEaten;
				game.gameScore = data.numApplesEaten * game.gameScoreModifier;
				data.snakeHitSound.play();
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

			data.scoreCountText.setString("Score: " + std::to_string(game.gameScore));

			if (data.snake.tail.size() + 1 == NUM_CELLS_ON_SCREEN)
			{
				game.isGameWon = true;
			}
		}

	}

	void SpawnAppleInAvailableCell(GameStatePlayingData& data)
	{
		MarkUnavailableCells(data);
		MarkWallCellsAsUnavailable(data);
		data.grid.GetAvailableCells();
		data.apple.position = data.grid.GetRandomAvailableCell();
		data.apple.position.x = data.apple.position.x * TILE_SIZE + TILE_SIZE / 2;
		data.apple.position.y = data.apple.position.y * TILE_SIZE + TILE_SIZE / 2;
	}

	void MarkUnavailableCells(GameStatePlayingData& data)
	{
		for (int i = 0; i < GRID_CELLS_HORIZONTAL; ++i)
		{
			for (int j = 0; j < GRID_CELLS_VERTICAL; ++j)
			{
				if (data.snake.position == data.grid.GetCellCoordinatesOnScreen(i, j)) //marking all cells as available but the one that is in contact with snake's head
				{
					data.grid.cell[i][j].isAvailable = false;
				}
				else
				{
					data.grid.cell[i][j].isAvailable = true;
				}

				for (const auto& segment : data.snake.tail) //marking cells with snake's tail in there as unavailable
				{
					if (segment.position == data.grid.GetCellCoordinatesOnScreen(i, j))
					{
						data.grid.cell[i][j].isAvailable = false;
					}
				}
			}
			
		}
	}
	void MarkWallCellsAsUnavailable(GameStatePlayingData& data)
	{
		for (int i = 0; i < GRID_CELLS_HORIZONTAL; ++i)
		{
			for (int j = 0; j < GRID_CELLS_VERTICAL; ++j)
			{
				if (i == 0 || i == GRID_CELLS_HORIZONTAL - 1 || j == 0 || j == GRID_CELLS_VERTICAL - 1)
				{
					data.grid.cell[i][j].isAvailable = false;
					data.grid.cell[i][j].wallSprite.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
					data.grid.cell[i][j].wallSprite.setFillColor(sf::Color::Red);
					data.grid.cell[i][j].wallSprite.setPosition(sf::Vector2f(data.grid.cell[i][j].position.x * TILE_SIZE, data.grid.cell[i][j].position.y * TILE_SIZE));
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
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		for (int i = 0; i < GRID_CELLS_HORIZONTAL; ++i)
		{
			for (int j = 0; j < GRID_CELLS_VERTICAL; ++j)
			{
				window.draw(data.grid.cell[i][j].wallSprite);
			}
		}
		
		DrawSnake(data.snake, window);
		DrawApple(data.apple, window);
		window.draw(data.scoreCountText);
		while (data.timeSinceGameStarted <= PAUSE_TIME_IN_SECONDS_BEFORE_GAME_STARTS)
		{
			window.draw(data.playingInputClueText);
			if (data.timeSinceGameStarted < 1)
			{
				data.countdownText.setString("3");
			}
			else if (data.timeSinceGameStarted < 2)
			{
				data.countdownText.setString("2");
			}
			else if (data.timeSinceGameStarted < 3)
			{
				data.countdownText.setString("1");
			}

			window.draw(data.countdownText);
			break;
		}
	}
	void ShutDownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		//nothing to deinit here yet
	}
}
