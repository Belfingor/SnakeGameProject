#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.h"



namespace SnakeGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float deltaTime);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
	void ShutDownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
}