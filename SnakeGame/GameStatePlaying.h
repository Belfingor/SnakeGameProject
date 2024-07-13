#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Snake.h"
#include "Apple.h"
#include "Math.h"
#include "Game.h"


namespace SnakeGame
{
	struct Game;
	struct Cell
	{
		// Identify coordinates in cell system
		Position2D position;
		bool isAvailable = true;
		sf::RectangleShape wallSprite;
	};
	struct Grid
	{
		Cell cell[GRID_CELLS_HORIZONTAL][GRID_CELLS_VERTICAL];

		void InitGrid()
		{
			for (int x = 0; x < GRID_CELLS_HORIZONTAL; ++x)
			{
				for (int y = 0; y < GRID_CELLS_VERTICAL; ++y)
				{
					cell[x][y].position.x = x;
					cell[x][y].position.y = y;
				}
			}
		}

		Position2D GetCellCoordinatesOnScreen(int x, int y)
		{
			Position2D screenPos;
			screenPos.x = cell[x][y].position.x * TILE_SIZE + 20;
			screenPos.y = cell[x][y].position.y * TILE_SIZE + 20;
			return screenPos;
		}

		std::vector<Cell> GetAvailableCells()
		{
			std::vector<Cell> availableCells;
			for (int x = 0; x < GRID_CELLS_HORIZONTAL; ++x)
			{
				for (int y = 0; y < GRID_CELLS_VERTICAL; ++y)
				{
					if (cell[x][y].isAvailable)
					{
						availableCells.push_back(cell[x][y]);
					}
				}
			}
			return availableCells;
		}

		Position2D GetRandomAvailableCell()
		{
			std::vector<Cell> availableCells = GetAvailableCells();
			int randomAvailableIndex = std::rand() % availableCells.size();
			availableCells[randomAvailableIndex].position.x;
			availableCells[randomAvailableIndex].position.y;
			return availableCells[randomAvailableIndex].position;
		}
	};

	//--------------------------------------------------------------------------------

	struct GameStatePlayingData
	{
		Snake snake;
		Apple apple;
		Grid grid;
		sf::Texture tileSetTexture; // Loading tile set here as it is used for all sprites possible
		sf::Font font;
		sf::Sound snakeHitSound;
		sf::SoundBuffer snakeHitSoundBuffer;
	

		int numApplesEaten = 0; // For counting scores
		float timeSinceGameStarted = 0;
		
		//UI data
		sf::Text scoreCountText;
		sf::Text countdownText;
		sf::Text playingInputClueText;
	};
	//--------------------------------------------------------------------------------

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime);
	void SpawnAppleInAvailableCell(GameStatePlayingData& data);
	void MarkUnavailableCells(GameStatePlayingData& data);
	void MarkWallCellsAsUnavailable(GameStatePlayingData& data);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event); // TO BE COMPLETED WHEN STATE LOGIC IS DONE
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
	void ShutDownGameStatePlaying(GameStatePlayingData& data, Game& game);
}
