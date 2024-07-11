#include "GameStateGameOver.h"


namespace SnakeGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile("Resources/Fonts/Roboto-BlackItalic.ttf"));

		
		data.gameOverText.setFont(data.font);
		data.gameOverText.setCharacterSize(48);
		if (game.isGameWon == true)
		{
			data.gameOverText.setString("YAY YOU WON!");
			data.gameOverText.setFillColor(sf::Color::Green);
			data.gameOverText.setPosition(SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.5f);
		}
		else if (game.isGameWon == false)
		{
			data.gameOverText.setString("GAME OVER");
			data.gameOverText.setFillColor(sf::Color::Red);
			data.gameOverText.setPosition(SCREEN_WIDTH / 2.9f, SCREEN_HEIGHT / 2.5f);
		}
		

		data.gameOverInputClueText.setFont(data.font);
		data.gameOverInputClueText.setCharacterSize(24);
		data.gameOverInputClueText.setFillColor(sf::Color::Yellow);
		data.gameOverInputClueText.setPosition(20, 6);
		data.gameOverInputClueText.setString("Restart (Space)\nMain Menu (ESC)");

		data.gameOverDifficultyText.setFont(data.font);
		data.gameOverDifficultyText.setCharacterSize(24);
		data.gameOverDifficultyText.setFillColor(sf::Color::White);
		data.gameOverDifficultyText.setPosition(10, SCREEN_HEIGHT - 34);
		data.gameOverDifficultyText.setString("Difficulty (Enter) - "+ game.diffivultyString);
	}
	void ShutDownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		game.isGameWon = false;
	}
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(game, GameStateType::Playing);
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				ChangeDifficultyLevel(game, event);
			}
		}
	}
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float deltaTime)
	{
		data.gameOverDifficultyText.setString("Difficulty (Enter) - " + game.diffivultyString);
	}
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.gameOverText);
		window.draw(data.gameOverInputClueText);
		window.draw(data.gameOverDifficultyText);
	}
}