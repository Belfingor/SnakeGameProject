#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace SnakeGame;

int main()
{
	//--------------------------------------------------------------------------------
	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game");
	window.setFramerateLimit(10); // Reduce framrate to not spam CPU and GPU and keep game consistent on any PC
	
	//--------------------------------------------------------------------------------
	Game game;
	InitGame(game);

	// Init Game Clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	//--------------------------------------------------------------------------------
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

	while (window.isOpen())
	{
		// Calculate Delta Time (didnt use it anywhere yet but may need in the future)
		float currentTime = gameClock.getElapsedTime().asMicroseconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // TEMPORARY
			{
				window.close();
			}
		}

		UpdateGame(game, window);
		
		window.clear();
		DrawGame(game, window);
		window.draw(gridLines); // Drawing grid lines that are used for visual reference
		window.display();
	}
	return 0;
}

