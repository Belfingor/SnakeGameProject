#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"
#include "Apple.h"

namespace SnakeGame
{
	struct Apple;

	//Init tail structure. Have to declare it before snake struct so vector can use it
	struct SnakeTail
	{
		float tailX = 0;
		float tailY = 0;
		sf::RectangleShape tailShape;
	};

	//Init Snake data
	struct Snake
	{
		float snakeX = 0;
		float snakeY = 0;
		float snakeSpeed = SNAKE_SPEED;
		int snakeDirection = 0; //0 - Right, 1 - Up, 2 - Left, 3 - Down.
		//int desiredDirection = 0; //gonna use it to create grid movement
		sf::RectangleShape snakeShape;
		std::vector<SnakeTail> tail; //Vector for snake's tail
		SnakeTail tailSegment;

		//creating tail Leash to store snake coordinates from previous frame and make first tail segment follow it 
		float tailLeashX = 0;
		float tailLeashY = 0;
	};


	void InitSnake(Snake& snake);
	//--------------------------------- snake's tail functions 
	void InitSnakeTail(Snake& snake);
	void UpdateSnakeTail(Snake& snake);
	void DrawSnakeTail(sf::RenderWindow& window, Snake& snake);
	//---------------------------------
	void HandleInput(Snake& snake);
	void UpdateSnakeState(Snake& snake, Apple& apple);
	void UpdateSnakePositionOnScreen(Snake& snake, sf::RenderWindow& window);
}