#include "Snake.h"
#include "Math.h"
#include <vector>

namespace SnakeGame
{
	void InitSnake(Snake& snake)
	{
		// Starting coordinates for snake
		snake.snakeX = SCREEN_WIDTH / 2.f - 20.f;
		snake.snakeY = SCREEN_HEIGHT / 2.f;
		snake.snakeSpeed = SNAKE_SPEED;
		snake.snakeDirection = 0;

		// Init SnakeHeadSprite here
		snake.snakeHeadSprite.setTextureRect(sf::IntRect(8, 63, 8, 8));
		snake.snakeHeadSprite.setScale(5, 5);
		snake.snakeHeadSprite.setOrigin(SNAKE_SIZE / 10.f, SNAKE_SIZE / 10.f); 

		InitSnakeTail(snake);
	}

	void InitSnakeTail(Snake& snake)
	{
		// Init Tail Sprite here
		snake.tailSegment.snakeTailSprite.setTextureRect(sf::IntRect(40, 63, 8, 8));
		snake.tailSegment.snakeTailSprite.setScale(5, 5);
		snake.tailSegment.snakeTailSprite.setOrigin(SNAKE_SIZE / 10.f, SNAKE_SIZE / 10.f);

		for (int i = 0; i < NUM_TAILS; ++i)
		{
			// Init tail segment position
			snake.tailSegment.tailX = snake.snakeX;
			snake.tailSegment.tailY = snake.snakeY;

			snake.tail.push_back(snake.tailSegment); // Add the tail segment to the snake's tail vector
		}
	} 

	void UpdateSnakeTail(Snake& snake)
	{
		// Update position of each segment to follow the previous segment (I mean "next" segment hehe)
  		for (size_t i = snake.tail.size() - 1; i > 0; --i)
		{
			snake.tail[i].tailX = snake.tail[i - 1].tailX;
			snake.tail[i].tailY = snake.tail[i - 1].tailY;
			snake.tail[i].snakeTailSprite.setPosition(snake.tail[i].tailX, snake.tail[i].tailY);
		}

		// Update first segment to follow snake's head
		if (!snake.tail.empty())
		{
			snake.tail[0].tailX = snake.tailLeashX ;
			snake.tail[0].tailY = snake.tailLeashY;
			snake.tail[0].snakeTailSprite.setPosition(snake.tail[0].tailX, snake.tail[0].tailY);
		}
	}



	void HandleInput(Snake& snake)
	{
		//Setting only desired direction so it can follow grid movement bla...
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.snakeDirection != 2)
		{
			snake.desiredDirection = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.snakeDirection != 3)
		{
			snake.desiredDirection = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.snakeDirection != 0)
		{
			snake.desiredDirection = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.snakeDirection != 1)
		{
			snake.desiredDirection = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //THIS IS FOR TESTING PURPOSES WILL BE DELETED LATER
		{
			snake.tail.push_back(snake.tailSegment);
		}

	}

	void UpdateSnakeState(Snake& snake, Apple& apple) //include Apple only because of the apple collision function (will move it later(maybe))
	{
		if (snake.snakeDirection == 0) // Right
		{
			snake.tailLeashX = snake.snakeX;
			snake.tailLeashY = snake.snakeY;
			snake.snakeX = snake.snakeX + snake.snakeSpeed;
			snake.snakeHeadSprite.setTextureRect(sf::IntRect(32, 63, 8, 8));
			ChangeSnakeDirection(snake);
		}
		else if (snake.snakeDirection == 1) // Up
		{
			snake.tailLeashY = snake.snakeY;
			snake.tailLeashX = snake.snakeX;
			snake.snakeY = snake.snakeY - snake.snakeSpeed;
			snake.snakeHeadSprite.setTextureRect(sf::IntRect(8, 63, 8, 8));
			ChangeSnakeDirection(snake);
		}
		else if (snake.snakeDirection == 2) // Left
		{
			snake.tailLeashX = snake.snakeX;
			snake.tailLeashY = snake.snakeY;
			snake.snakeX = snake.snakeX - snake.snakeSpeed;
			snake.snakeHeadSprite.setTextureRect(sf::IntRect(16, 63, 8, 8));
			ChangeSnakeDirection(snake);
		}
		else if (snake.snakeDirection == 3) // Down
		{
			snake.tailLeashY = snake.snakeY;
			snake.tailLeashX = snake.snakeX;
			snake.snakeY = snake.snakeY + snake.snakeSpeed;
			snake.snakeHeadSprite.setTextureRect(sf::IntRect(24, 63, 8, 8));
			ChangeSnakeDirection(snake);
		}

		if (DidSnakeCollideWithApple(snake, apple)) //checking here if snake collided with apple
		{
			snake.tail.push_back(snake.tailSegment);
		}

		

		UpdateSnakeTail(snake); //going to update tail state here as well
		snake.snakeHeadSprite.setPosition(snake.snakeX, snake.snakeY);
		
	}

	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		for (const auto& segment : snake.tail)
		{	
			window.draw(segment.snakeTailSprite);
 		}
		window.draw(snake.snakeHeadSprite);
	}

	void ChangeSnakeDirection(Snake& snake)
	{
		if (DoSnakeAndCellCoordinatesMatch(snake))    // To adjust Grid movement
		{
			snake.snakeDirection = snake.desiredDirection;
		}
	}
}






 