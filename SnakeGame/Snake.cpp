#include "Snake.h"
#include <vector>



namespace SnakeGame
{
	void InitSnake(Snake& snake)
	{
		// Starting coordinates for snake
		snake.position.x = SCREEN_WIDTH / 2.f - 20.f;
		snake.position.y = SCREEN_HEIGHT / 2.f;
		snake.snakeSpeed = SNAKE_MOVEMENT_PER_FRAME;
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
			snake.tailSegment.position.x = snake.position.x - TILE_SIZE;
			snake.tailSegment.position.y = snake.position.y;

			snake.tail.push_back(snake.tailSegment); // Add the tail segment to the snake's tail vector
		}
	} 

	void UpdateSnakeTail(Snake& snake)
	{
		// Update position of each segment to follow the previous segment (a segment in front of it)
  		for (size_t i = snake.tail.size() - 1; i > 0; --i)
		{
			snake.tail[i].position.x = snake.tail[i - 1].position.x;
			snake.tail[i].position.y = snake.tail[i - 1].position.y;
			snake.tail[i].snakeTailSprite.setPosition(snake.tail[i].position.x, snake.tail[i].position.y);
		}

		// Update first segment to follow snake's head
		if (!snake.tail.empty())
		{
			snake.tail[0].position.x = snake.tailLeashX ;
			snake.tail[0].position.y = snake.tailLeashY;
			snake.tail[0].snakeTailSprite.setPosition(snake.tail[0].position.x, snake.tail[0].position.y);
		}
	}



	void HandleInput(Snake& snake)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.snakeDirection != 2)
		{
			snake.snakeDirection = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.snakeDirection != 3)
		{
			snake.snakeDirection = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.snakeDirection != 0)
		{
			snake.snakeDirection = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.snakeDirection != 1)
		{
			snake.snakeDirection = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // THIS IS FOR TESTING PURPOSES WILL BE DELETED LATER
		{
			snake.tail.push_back(snake.tailSegment);
		}

	}

	void UpdateSnakeState(Snake& snake)
	{
		snake.tailLeashX = snake.position.x;
		snake.tailLeashY = snake.position.y;
	
		if (snake.snakeDirection == 0) // Right
		{
			snake.position.x = snake.position.x + snake.snakeSpeed;
			snake.snakeHeadSprite.setTextureRect(sf::IntRect(32, 63, 8, 8));
		}
		else if (snake.snakeDirection == 1) // Up
		{
			snake.position.y = snake.position.y - snake.snakeSpeed;
			snake.snakeHeadSprite.setTextureRect(sf::IntRect(8, 63, 8, 8));
		}
		else if (snake.snakeDirection == 2) // Left
		{
			snake.position.x = snake.position.x - snake.snakeSpeed;
			snake.snakeHeadSprite.setTextureRect(sf::IntRect(16, 63, 8, 8));
		}
		else if (snake.snakeDirection == 3) // Down
		{
			snake.position.y = snake.position.y + snake.snakeSpeed;
			snake.snakeHeadSprite.setTextureRect(sf::IntRect(24, 63, 8, 8));
		}

		UpdateSnakeTail(snake); // Going to update tail state here as well
		snake.snakeHeadSprite.setPosition(snake.position.x, snake.position.y); 
	}

	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		for (const auto& segment : snake.tail)
		{	
			window.draw(segment.snakeTailSprite);
 		}
		window.draw(snake.snakeHeadSprite);
	}

	Rectangle GetSnakeHeadCollider(const Snake& snake)
	{
		return { { snake.position.x - SNAKE_SIZE / 2.f, snake.position.y - SNAKE_SIZE / 2.f },
			{ SNAKE_SIZE, SNAKE_SIZE } };
	}


	// Getting screen collider here for snake_boarder collision
	Rectangle GetScreenColloder()
	{
		return { {0.f, 0.f} ,{ SCREEN_WIDTH - TILE_SIZE + 1, SCREEN_HEIGHT - TILE_SIZE + 1} };
	}

	std::vector<Rectangle> GetSnakeTailCollider(const Snake& snake)
	{
		std::vector<Rectangle> colliders;
		for (const auto& segment : snake.tail)
		{
			colliders.push_back({ segment.position.x - SNAKE_SIZE / 2.f, segment.position.y - SNAKE_SIZE / 2.f, SNAKE_SIZE, SNAKE_SIZE });
		}
		return colliders;
	}
}






 