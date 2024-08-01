#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.h"
#include "Game.h"

namespace SnakeGame
{
	struct GameStateAddToScoreboardData
	{
		sf::Font font;
		sf::Text playerScoreText;
		MenuItem yesItem;
		MenuItem noItem;
		MenuItem typingNameTextItem;
		Menu menu; //will use the same logic as main menu

		sf::Sound hoverSound;
		sf::SoundBuffer hoverSoundBuffer;
		sf::Sound gameOverSound;
		sf::SoundBuffer gameOverSoundBuffer;
	};

	void InitGameStateAddToScoarboard(GameStateAddToScoreboardData& data, Game& game);
	void UpdateGameStateAddToScoreboard(GameStateAddToScoreboardData& data, Game& game, float deltaTime);
	void HandleGameStateAddToScoreboardWindowEvent(GameStateAddToScoreboardData& data, Game& game, const sf::Event& event);
	void DrawGameStateAddToScoreboard(GameStateAddToScoreboardData& data, Game& game, sf::RenderWindow& window);
	void ShutDownGameStateAddToScoreboard(GameStateAddToScoreboardData& data, Game& game);
}

