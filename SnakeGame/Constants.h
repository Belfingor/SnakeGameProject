#pragma once

namespace SnakeGame
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const unsigned int GRID_CELLS_HORIZONTAL = 20;
	const unsigned int GRID_CELLS_VERTICAL = 15;
	const int GRID_SELL_SIZE = SCREEN_HEIGHT / GRID_CELLS_VERTICAL; 

	const int SNAKE_SIZE = GRID_SELL_SIZE;
	const int SNAKE_SPEED = 40.f;
	const int NUM_TAILS = 3;
}

