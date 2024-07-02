#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>


namespace SnakeGame
{
	struct Game;

	struct GameStateExitDialogData
	{
		sf::Font font;
		sf::Text exitHintText;
	};

	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void ShutDownGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event);
	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float deltaTime);
	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window);
}