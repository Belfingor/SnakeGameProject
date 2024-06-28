#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>

namespace SnakeGame
{
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

	//--------------------------------------------------------------------------------

	enum class Orientation
	{
		Horizontal = 0,
		Vertical
	};

	enum class Alignment
	{
		Min, //Left or Top
		Mid,
		Max //Right or Top
	};

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);
	/*bool DidSnakeCollideWithWall(Snake& snake);
	bool DidSnakeCollideWithTail(Snake& snake);*/
}