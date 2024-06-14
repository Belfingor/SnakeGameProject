#pragma once

namespace SnakeGame
{
	struct Snake;
	struct Apple;

	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};

	typedef Vector2D Position2D;

	struct Rectangle
	{
		Position2D position; 
		Vector2D size;
	};

	bool DoShapesCollide(const Rectangle& rectangle1, const Rectangle& rectangle2);

	bool DidSnakeCollideWithWall(Snake& snake);
	bool DidSnakeCollideWithTail(Snake& snake);
}