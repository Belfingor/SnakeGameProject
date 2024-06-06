#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"
#include "Apple.h"
#include "Math.h"

using namespace SnakeGame;

int main()
{
	//--------------------------------------------------------------------------------
	//Init seed for Rand functions
	int seed = (int)time(nullptr);
	srand(seed);

	// Init Window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game");

	//Init Game Clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();
	//--------------------------------------------------------------------------------

	//Init Snake and Invisible Grid for movement
	Snake snake;
	Grid grid;
	Apple apple;
	InitSnake(snake); // also includes tail initiation
	InitGrid(grid);
	InitApple(apple);


	//--------------------------------------------------------------------------------
	// Lets try to draw my grid here
	// Here I Basically drow the grid for visual reference. Will be deleted in final
	sf::VertexArray gridLines(sf::Lines);

	// Horizontal lines
	for (unsigned int i = 0; i <= GRID_CELLS_VERTICAL; ++i) {
		gridLines.append(sf::Vertex(sf::Vector2f(0, i * (SCREEN_WIDTH / GRID_CELLS_HORIZONTAL)), sf::Color::White));
		gridLines.append(sf::Vertex(sf::Vector2f(SCREEN_WIDTH, i * (SCREEN_WIDTH / GRID_CELLS_HORIZONTAL)), sf::Color::White));
	}

	// Vertical lines
	for (unsigned int i = 0; i <= GRID_CELLS_HORIZONTAL; ++i) {
		gridLines.append(sf::Vertex(sf::Vector2f(i * (SCREEN_HEIGHT / GRID_CELLS_VERTICAL), 0), sf::Color::White));
		gridLines.append(sf::Vertex(sf::Vector2f(i * (SCREEN_HEIGHT / GRID_CELLS_VERTICAL), SCREEN_HEIGHT), sf::Color::White));
	}
	//--------------------------------------------------------------------------------



	//Main loop
	while (window.isOpen())
	{
		// Reduce framrate to not spam CPU and GPU
		sf::sleep(sf::milliseconds(120));

		//Calculate Delta Time
		float currentTime = gameClock.getElapsedTime().asMicroseconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		/*if (DoSnakeAndCellCoordinatesMatch(snake))        //GONNA TRY WITHOUT IT
		{
			snake.snakeDirection = snake.desiredDirection;
		}*/



		HandleInput(snake);
		//snake movement updates
		UpdateSnakeState(snake, apple);


		//check for border collision
		if (DidSnakeCollideWithWall(snake))
		{
			window.close();
		}

		if (DidSnakeCollideWithTail(snake))
		{
			window.close();
		}

		//check if apple is eaten
		if (DidSnakeCollideWithApple(snake, apple))
		{
			SetRandomPositionForApple(apple);
		}


		window.clear();
		UpdateSnakePositionOnScreen(snake, window);
		DrawSnakeTail(window, snake);
		window.draw(apple.appleShape); //drawing apple here will make it a funtion later
		window.draw(gridLines);
		window.display();
	}


	return 0;
}

