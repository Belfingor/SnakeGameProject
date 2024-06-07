#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Apple.h"
//#include <vector>


namespace SnakeGame
{
	struct Apple;

	//Init tail structure. Have to declare it before snake struct so vector can use it
	struct SnakeTail
	{
		float tailX = 0;
		float tailY = 0;
		
		sf::RectangleShape tailShape;
		sf::Sprite snakeTailSprite;
		
	};

	//Init Snake data
	struct Snake
	{
		float snakeX = 0;
		float snakeY = 0;
		float snakeSpeed = SNAKE_SPEED;
		int snakeDirection = 0; //0 - Right, 1 - Up, 2 - Left, 3 - Down.
		SnakeTail tailSegment; // Include Tail data to snakes data
		std::vector<SnakeTail> tail; //Vector for snake's tail
		
		
		
		//creating tail Leash to store snake coordinates from previous frame and make first tail segment follow it 
		float tailLeashX = 0;
		float tailLeashY = 0;

		// Set the snake sprite from previously loaded TileSet 
		sf::Sprite snakeHeadSprite;
		
		
	};


	void InitSnake(Snake& snake);
	//--------------------------------- snake's tail functions 
	void InitSnakeTail(Snake& snake);
	void UpdateSnakeTail(Snake& snake);
	//---------------------------------
	void HandleInput(Snake& snake);
	void UpdateSnakeState(Snake& snake, Apple& apple);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);
}