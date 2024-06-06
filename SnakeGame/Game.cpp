#include "Game.h"

namespace SnakeGame
{
	void InitGrid(Grid& grid) //will use this grid later for apple spawn, but now it is just for visualisation
	{
		for (int i = 0; i < GRID_CELLS_HORIZONTAL; ++i)
		{
			for (int j = 0; j < GRID_CELLS_VERTICAL; ++j)
			{
				grid.cell[i][j].x = i * (SCREEN_WIDTH / GRID_CELLS_HORIZONTAL); //X coordinate of cell on screen
				grid.cell[i][j].y = i * (SCREEN_HEIGHT / GRID_CELLS_VERTICAL); //Y coordinate of cell on screen
			}
		}
	}
}












// here we gonna return TRUE only if snake's head is fully in cell               //GONNA TRY WITHOUT IT
//bool DoSnakeAndCellCoordinatesMatch(Snake& snake)             
//{
//	return (static_cast<int>(snake.snakeX) % (SCREEN_WIDTH / GRID_CELLS_HORIZONTAL) - GRID_SELL_SIZE / 2== 0) //use static_cast to convert float to int
//		&& (static_cast<int>(snake.snakeY) % (SCREEN_HEIGHT / GRID_CELLS_VERTICAL) - GRID_SELL_SIZE/2 == 0);
//}