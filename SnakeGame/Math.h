#pragma once

namespace SnakeGame
{
	struct Snake;
	struct Apple;

	struct Vector2D
	{
		float x = 0;
		float y = 0;

		bool operator==(const Vector2D& other) const
		{
			return x == other.x && y == other.y;
		}
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