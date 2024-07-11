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
	window.setFramerateLimit(FRAMES_PER_SECOND);
	
	//--------------------------------------------------------------------------------
	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

	// Init Game Clock
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
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
	return 0;
}

