#include <cassert>
#include "GameStateAddToScoreboard.h"
#include "Scoreboard.h"


namespace SnakeGame
{
	void InitGameStateAddToScoarboard(GameStateAddToScoreboardData& data, Game& game)
	{
		assert(data.font.loadFromFile("Resources/Fonts/Roboto-BlackItalic.ttf"));
		assert(data.hoverSoundBuffer.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav"));

		data.playerScoreText.setString("Your Score: " + std::to_string(game.scoreboardData.playerScore));
		data.playerScoreText.setFont(data.font);
		data.playerScoreText.setCharacterSize(24);
		data.playerScoreText.setFillColor(sf::Color::White);
		data.playerScoreText.setPosition(SCREEN_WIDTH / 2, 20);

		data.menu.rootItem.hintText.setString("Add to Scoreboard?");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childOrientation = Orientation::Vertical;
		data.menu.rootItem.childAlignment = Alignment::Mid;
		data.menu.rootItem.childSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.noItem);
		data.menu.rootItem.children.push_back(&data.yesItem);

		data.noItem.text.setString("No");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		data.yesItem.text.setString("Yes");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);
		data.yesItem.hintText.setString("Type your name\nand press Enter");
		data.yesItem.hintText.setFont(data.font);
		data.yesItem.hintText.setCharacterSize(48);
		data.yesItem.hintText.setFillColor(sf::Color::Red);
		data.yesItem.childOrientation = Orientation::Vertical;
		data.yesItem.childAlignment = Alignment::Max;
		data.yesItem.childSpacing = 10.f;
		data.yesItem.children.push_back(&data.typingNameTextItem);

		data.typingNameTextItem.text.setString("123");
		data.typingNameTextItem.text.setFont(data.font);
		data.typingNameTextItem.text.setCharacterSize(24);
		data.typingNameTextItem.text.setFillColor(sf::Color::Blue);

		data.hoverSound.setBuffer(data.hoverSoundBuffer);
		data.hoverSound.setVolume(50.f);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.noItem);
		InitScoreboard(game.scoreboardData);
	}

	void UpdateGameStateAddToScoreboard(GameStateAddToScoreboardData& data, Game& game, float deltaTime)
	{
		// Nothing to Update Here
	}

	void HandleGameStateAddToScoreboardWindowEvent(GameStateAddToScoreboardData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				data.hoverSound.play();
				if (data.menu.selectedItem == &data.noItem)
				{
					SwitchGameState(game, GameStateType::GameOver);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.typingNameTextItem)
				{
					SwitchGameState(game, GameStateType::GameOver);
					AddPlayerScoreToScoreboard(game.scoreboardData);
				}
			}
			
			Orientation orientation = data.menu.selectedItem->parent->childOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				data.hoverSound.play();
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				data.hoverSound.play();
				SelectNextMenuItem(data.menu);
			}
		}
		if (event.type == sf::Event::TextEntered && data.menu.selectedItem == &data.typingNameTextItem)
		{
			data.typingNameTextItem.text.setString(ScoreboardHandleInputEvents(game.scoreboardData, event));
		}
		
	}

	void DrawGameStateAddToScoreboard(GameStateAddToScoreboardData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });

		window.draw(data.playerScoreText);
		window.draw(game.scoreboardData.scoreboardText);
	}
	void ShutDownGameStateAddToScoreboard(GameStateAddToScoreboardData& data, Game& game)
	{
		//Nothing to shutdown here
	}
}