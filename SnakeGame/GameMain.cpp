#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"

using namespace SnakeGame;

int main()
{
	//--------------------------------------------------------------------------------
	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SnakeGame::SCREEN_WIDTH, SnakeGame::SCREEN_HEIGHT), "Snake Game");
	window.setFramerateLimit(11); // Reduce framrate to not spam CPU and GPU and keep game consistent on any PC
	
	//--------------------------------------------------------------------------------
	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

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
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		if (UpdateGame(*game, deltaTime))
		{
			window.clear();
			DrawGame(*game, window);
			window.display();
		}
		else
		{
			window.close();
		}
	}
	DeinitializeGame(*game);
	delete game;
	game = nullptr;
	//window.draw(gridLines); // Drawing grid lines that are used for visual reference
	return 0;
}

