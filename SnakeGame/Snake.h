#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"
#include "Math.h"


namespace SnakeGame
{
	// Init tail data. Have to declare it before snake struct so vector can use it
	struct SnakeTail
	{
		Position2D position;
		sf::Sprite snakeTailSprite;
	};

	struct Snake
	{
		Position2D position;
		float snakeSpeed = SNAKE_MOVEMENT_PER_FRAME;
		int snakeDirection = 0; // 0 - Right, 1 - Up, 2 - Left, 3 - Down. Will be enum class later
		SnakeTail tailSegment; // Include Tail data to snakes data to make it whole
		std::vector<SnakeTail> tail;

		// Creating tail Leash to store snake coordinates from previous frame and make first tail segment follow it 
		float tailLeashX = 0;
		float tailLeashY = 0;

		sf::Sprite snakeHeadSprite;
	};

	void InitSnake(Snake& snake);
	void InitSnakeTail(Snake& snake);
	void UpdateSnakeTail(Snake& snake);
	void HandleInput(Snake& snake);
	void UpdateSnakeState(Snake& snake);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);
	Rectangle GetSnakeHeadCollider(const Snake& snake);
	std::vector<Rectangle> GetSnakeTailCollider(const Snake& snake);
}