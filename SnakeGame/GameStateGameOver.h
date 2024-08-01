#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <cassert>
#include "GameStatePlaying.h"


namespace SnakeGame
{
	struct Game;

	struct GameStateGameOverData
	{
		sf::Font font;

		sf::Text gameOverText;
		sf::Text gameOverInputClueText;
		sf::Text gameOverDifficultyText;
	};

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutDownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float deltaTime);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
}