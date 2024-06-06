#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Snake.h"
#include "Apple.h"

namespace SnakeGame
{
	// Init Grid
	struct Cell
	{
		//Identify coordinates in cell system overall
		int x;
		int y;
	};
	struct Grid
	{
		//identify coordinates of cell on the screen in general
		float x;
		float y;
		Cell cell[GRID_CELLS_HORIZONTAL][GRID_CELLS_VERTICAL];
	};

	
	struct Game
	{
		//Snake snake; // I have some problems with this part probably use it somewhere else and have a naming issue
		Apple apple;
		Grid grid;
	};

	void InitGrid(Grid& grid);
	/*void InitGame(Game& game)
	{
		InitGrid(game.grid);
		InitSnake(game.snake);
	}*/
	
}




// here we gonna return TRUE only if snake's head is fully in cell
//bool DoSnakeAndCellCoordinatesMatch(Snake& snake);       //GONNA TRY WITHOUT IT