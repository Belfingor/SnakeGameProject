#include "GameStateExitDialog.h"
#include <cassert>


namespace SnakeGame
{
	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		assert(data.font.loadFromFile("Resources/Fonts/Roboto-BlackItalic.ttf"));

		data.exitHintText.setFont(data.font);
		data.exitHintText.setCharacterSize(24);
		data.exitHintText.setFillColor(sf::Color::White);
		data.exitHintText.setPosition(50, SCREEN_HEIGHT / 2.3);
		data.exitHintText.setString("PAUSE:\nReturn to main menu - Enter\nResume - Esc");
	}

	void ShutDownGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		// Nothing to shutdown here
	}

	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float deltaTime)
	{
		// Nothing to update here
	}

	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.exitHintText);
	}
}