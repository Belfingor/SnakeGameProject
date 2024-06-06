#include "Snake.h"
#include "Math.h"

namespace SnakeGame
{
	void InitSnake(Snake& snake)
	{
		snake.snakeX = SCREEN_WIDTH / 2.f - 20.f;
		snake.snakeY = SCREEN_HEIGHT / 2.f;
		snake.snakeSpeed = SNAKE_SPEED;
		snake.snakeDirection = 0;
		snake.snakeShape.setSize(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
		snake.snakeShape.setFillColor(sf::Color::Green);
		snake.snakeShape.setOrigin(SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f);
		snake.snakeShape.setPosition(snake.snakeX, snake.snakeY);

		InitSnakeTail(snake);
	}

	void InitSnakeTail(Snake& snake)
	{
		for (int i = 0; i < NUM_TAILS; ++i)
		{
			//init tail segment position
			snake.tailSegment.tailX = snake.snakeX - SNAKE_SIZE; //(i + 1)
			snake.tailSegment.tailY = snake.snakeY;

			//settings for tail sprite
			snake.tailSegment.tailShape.setSize(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
			snake.tailSegment.tailShape.setFillColor(sf::Color::Blue);
			snake.tailSegment.tailShape.setOrigin(SNAKE_SIZE / 2.f, SNAKE_SIZE / 2.f);
			snake.tailSegment.tailShape.setPosition(snake.tailSegment.tailX, snake.tailSegment.tailY);

			snake.tail.push_back(snake.tailSegment); // Add the tail segment to the snake's tail vector
		}

	}

	void UpdateSnakeTail(Snake& snake)
	{
		//Update position of each segment to follow the previous segment (I mean "next" segment hehe)
		for (size_t i = snake.tail.size() - 1; i > 0; --i)
		{
			snake.tail[i].tailX = snake.tail[i - 1].tailX;
			snake.tail[i].tailY = snake.tail[i - 1].tailY;
			snake.tail[i].tailShape.setPosition(snake.tail[i].tailX, snake.tail[i].tailY);
		}

		//Update first segment to follow snake's head
		if (!snake.tail.empty())
		{
			snake.tail[0].tailX = snake.tailLeashX;
			snake.tail[0].tailY = snake.tailLeashY;
			snake.tail[0].tailShape.setPosition(snake.tail[0].tailX, snake.tail[0].tailY);
		}
	}

	void DrawSnakeTail(sf::RenderWindow& window, Snake& snake)
	{
		for (const auto& segment : snake.tail)
		{
			window.draw(segment.tailShape);
		}
	}



	void HandleInput(Snake& snake)
	{
		//Setting only desired direction so it can follow grid movement bla...
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.snakeDirection != 2)
		{
			//snake.desiredDirection = 0;
			snake.snakeDirection = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.snakeDirection != 3)
		{
			//snake.desiredDirection = 1;
			snake.snakeDirection = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.snakeDirection != 0)
		{
			//snake.desiredDirection = 2;
			snake.snakeDirection = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.snakeDirection != 1)
		{
			//snake.desiredDirection = 3;
			snake.snakeDirection = 3;
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
		}
		else if (snake.snakeDirection == 1) // Up
		{
			snake.tailLeashY = snake.snakeY;
			snake.tailLeashX = snake.snakeX;
			snake.snakeY = snake.snakeY - snake.snakeSpeed;
		}
		else if (snake.snakeDirection == 2) // Left
		{
			snake.tailLeashX = snake.snakeX;
			snake.tailLeashY = snake.snakeY;
			snake.snakeX = snake.snakeX - snake.snakeSpeed;
		}
		else if (snake.snakeDirection == 3) // Down
		{
			snake.tailLeashY = snake.snakeY;
			snake.tailLeashX = snake.snakeX;
			snake.snakeY = snake.snakeY + snake.snakeSpeed;
		}

		if (DidSnakeCollideWithApple(snake, apple)) //checking here if snake collided with apple
		{
			snake.tail.push_back(snake.tailSegment);
		}

		UpdateSnakeTail(snake); //going to update tail state here as well
	}

	void UpdateSnakePositionOnScreen(Snake& snake)
	{
		snake.snakeShape.setPosition(snake.snakeX, snake.snakeY);
		
	}
}






 