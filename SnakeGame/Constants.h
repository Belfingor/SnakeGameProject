#pragma once

namespace SnakeGame
{
	//--------------------------------------------------------------------------------
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;
	//--------------------------------------------------------------------------------
	const unsigned int GRID_CELLS_HORIZONTAL = 20;
	const unsigned int GRID_CELLS_VERTICAL = 15;
	const float GRID_CELL_SIZE = SCREEN_WIDTH / GRID_CELLS_HORIZONTAL;
	//--------------------------------------------------------------------------------
	const float SNAKE_SIZE = GRID_CELL_SIZE;
	const int SNAKE_MOVEMENT_PER_FRAME = GRID_CELL_SIZE;
	const int NUM_TAILS = 2; //Init number of tail segments
	//--------------------------------------------------------------------------------
}


