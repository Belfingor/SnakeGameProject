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
		snake.direction = SnakeDirection::Right;

		// Init SnakeHeadSprite here
		snake.snakeHeadSprite.setTextureRect(sf::IntRect(32, 63, 8, 8));
		snake.snakeHeadSprite.setScale(5, 5);
		snake.snakeHeadSprite.setOrigin(TILE_SIZE / 10.f, TILE_SIZE / 10.f); 

		InitSnakeTail(snake);
		UpdateSnakePosition(snake); // Have to Update it here as well, so all sprite positions are in place
	}

	void InitSnakeTail(Snake& snake)
	{
		// Init Tail Sprite here
		snake.tailSegment.snakeTailSprite.setTextureRect(sf::IntRect(40, 63, 8, 8));
		snake.tailSegment.snakeTailSprite.setScale(5, 5);
		snake.tailSegment.snakeTailSprite.setOrigin(TILE_SIZE / 10.f, TILE_SIZE / 10.f);

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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.direction != SnakeDirection::Left &&
			snake.readyToTurn == true)
		{
			snake.direction = SnakeDirection::Right;
			snake.readyToTurn = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.direction != SnakeDirection::Down &&
			snake.readyToTurn == true)
		{
			snake.direction = SnakeDirection::Up;
			snake.readyToTurn = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.direction != SnakeDirection::Right &&
			snake.readyToTurn == true)
		{
			snake.direction = SnakeDirection::Left;
			snake.readyToTurn = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.direction != SnakeDirection::Up &&
			snake.readyToTurn == true)
		{
			snake.direction = SnakeDirection::Down;
			snake.readyToTurn = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // THIS IS FOR TESTING PURPOSES WILL BE DELETED LATER
		{
			snake.tail.push_back(snake.tailSegment);
		}
	}

	void UpdateSnakePosition(Snake& snake)
	{
		snake.tailLeashX = snake.position.x;
		snake.tailLeashY = snake.position.y;

		//if (snake.deltaTimeToMove > .6f)
		//{
			switch (snake.direction)
			{
			case SnakeDirection::Right:
				snake.position.x = snake.position.x + snake.snakeSpeed;
				snake.snakeHeadSprite.setTextureRect(sf::IntRect(32, 63, 8, 8));
				snake.deltaTimeToMove = 0.f;
				UpdateSnakeTail(snake);
				break;
			case SnakeDirection::Up:
				snake.position.y = snake.position.y - snake.snakeSpeed;
				snake.snakeHeadSprite.setTextureRect(sf::IntRect(8, 63, 8, 8));
				snake.deltaTimeToMove = 0.f;
				UpdateSnakeTail(snake);
				break;
			case SnakeDirection::Left:
				snake.position.x = snake.position.x - snake.snakeSpeed;
				snake.snakeHeadSprite.setTextureRect(sf::IntRect(16, 63, 8, 8));
				snake.deltaTimeToMove = 0.f;
				UpdateSnakeTail(snake);
				break;
			case SnakeDirection::Down:
				snake.position.y = snake.position.y + snake.snakeSpeed;
				snake.snakeHeadSprite.setTextureRect(sf::IntRect(24, 63, 8, 8));
				snake.deltaTimeToMove = 0.f;
				UpdateSnakeTail(snake);
				break;
			}
			snake.readyToTurn = true;
	//	}

		
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
		return { { snake.position.x - TILE_SIZE / 2.f, snake.position.y - TILE_SIZE / 2.f },
			{ TILE_SIZE, TILE_SIZE } };
	}


	// Getting screen collider here for snake_boarder collision
	Rectangle GetScreenColloder()
	{
		return { {TILE_SIZE, TILE_SIZE} ,{ SCREEN_WIDTH - TILE_SIZE*2, SCREEN_HEIGHT - TILE_SIZE*2} };
	}

	std::vector<Rectangle> GetSnakeTailCollider(const Snake& snake)
	{
		std::vector<Rectangle> colliders;
		for (const auto& segment : snake.tail)
		{
			colliders.push_back({ segment.position.x - TILE_SIZE / 2.f, segment.position.y - TILE_SIZE / 2.f, TILE_SIZE, TILE_SIZE });
		}
		return colliders;
	}
}






 