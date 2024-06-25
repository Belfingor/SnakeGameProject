#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Snake.h"
#include "Apple.h"
#include "Math.h"


namespace SnakeGame
{
	//--------------------------------------------------------------------------------
	struct Cell
	{
		// Identify coordinates in cell system overall
		Position2D position;
		bool isAvailable = true;
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
			screenPos.x = cell[x][y].position.x * GRID_CELL_SIZE + 20;
			screenPos.y = cell[x][y].position.y * GRID_CELL_SIZE + 20;
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

	struct Game
	{
		Snake snake;
		Apple apple;
		Grid grid;
		sf::Texture tileSetTexture; // Loading tile set here as it is used for all sprites possible
	};
	//--------------------------------------------------------------------------------

	void InitGame(Game& game);
	void UpdateGame(Game& game, sf::RenderWindow& window);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void RespawnAppleInAvailableCell(Game& game);
	void MarkUnavailableCells(Game& game);
}
