#pragma once

namespace SnakeGame
{
	//--------------------------------------------------------------------------------
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;
	//--------------------------------------------------------------------------------
	const unsigned int GRID_CELLS_HORIZONTAL = 20;
	const unsigned int GRID_CELLS_VERTICAL = 15;
	const float TILE_SIZE = SCREEN_WIDTH / GRID_CELLS_HORIZONTAL;
	const int NUM_CELLS_ON_SCREEN = GRID_CELLS_HORIZONTAL * GRID_CELLS_VERTICAL;
	//--------------------------------------------------------------------------------
	const int SNAKE_MOVEMENT_PER_FRAME = TILE_SIZE;
	const int NUM_TAILS = 2; //Init number of tail segments
	//--------------------------------------------------------------------------------
	const float PAUSE_TIME_IN_SECONDS = 3.f;
	const int FRAMES_PER_SECOND = 10;
}


