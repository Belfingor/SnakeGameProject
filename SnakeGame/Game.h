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
		int x;
		int y;
	};
	struct Grid
	{
		// Identify coordinates of cell on the screen in general
		float x;
		float y;
		Cell cell[GRID_CELLS_HORIZONTAL][GRID_CELLS_VERTICAL];
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

	void InitGrid(Grid& grid);
	void InitGame(Game& game);
	void UpdateGame(Game& game, sf::RenderWindow& window);
	void DrawGame(Game& game, sf::RenderWindow& window);
}