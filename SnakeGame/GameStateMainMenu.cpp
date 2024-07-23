#include "GameStateMainMenu.h"
#include <cassert> 
#include "Game.h"

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile("Resources/Fonts/Roboto-BlackItalic.ttf"));
		assert(data.hoverSoundBuffer.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav"));
		assert(data.enterSoundBuffer.loadFromFile("Resources/Sounds/Timgormly__Enter.wav"));

		data.menu.rootItem.hintText.setString("SNAKE GAME");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childOrientation = Orientation::Vertical;
		data.menu.rootItem.childAlignment = Alignment::Mid;
		data.menu.rootItem.childSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		// Insert more items here ---->
		data.menu.rootItem.children.push_back(&data.settingsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		data.startGameItem.text.setString("Start game");
		data.startGameItem.text.setFont(data.font);
		data.startGameItem.text.setCharacterSize(24);

		data.exitGameItem.text.setString("Exit Game");
		data.exitGameItem.text.setFont(data.font);
		data.exitGameItem.text.setCharacterSize(24);
		data.exitGameItem.hintText.setString("Are you sure?");
		data.exitGameItem.hintText.setFont(data.font);
		data.exitGameItem.hintText.setCharacterSize(48);
		data.exitGameItem.hintText.setFillColor(sf::Color::Red);
		data.exitGameItem.childOrientation = Orientation::Vertical;
		data.exitGameItem.childAlignment = Alignment::Mid;
		data.exitGameItem.childSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		data.yesItem.text.setString("Yes");
		data.yesItem.text.setFont(data.font);
		data.yesItem.text.setCharacterSize(24);

		data.noItem.text.setString("No");
		data.noItem.text.setFont(data.font);
		data.noItem.text.setCharacterSize(24);

		data.settingsItem.text.setString("Settings");
		data.settingsItem.text.setFont(data.font);
		data.settingsItem.text.setCharacterSize(24);
		data.settingsItem.hintText.setString("Game Settings");
		data.settingsItem.hintText.setFont(data.font);
		data.settingsItem.hintText.setCharacterSize(48);
		data.settingsItem.hintText.setFillColor(sf::Color::Red);
		data.settingsItem.childOrientation = Orientation::Vertical;
		data.settingsItem.childAlignment = Alignment::Max;
		data.settingsItem.childSpacing = 10.f;
		data.settingsItem.children.push_back(&data.difficultyItem);

		data.difficultyItem.text.setString("Difficulty - " + game.difficultyString);
		data.difficultyItem.text.setFont(data.font);
		data.difficultyItem.text.setCharacterSize(24);

		data.navigationHintText.setFont(data.font);
		data.navigationHintText.setCharacterSize(24);
		data.navigationHintText.setFillColor(sf::Color::White);
		data.navigationHintText.setPosition(20, 10);
		data.navigationHintText.setString("Arrows - Navigate\nEnter - Select\nEsc - Return");

		data.hoverSound.setBuffer(data.hoverSoundBuffer);
		data.hoverSound.setVolume(50.f);
		data.enterSound.setBuffer(data.enterSoundBuffer);
		data.enterSound.setVolume(50.f);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float deltaTime)
	{ 
		// Nothing to update here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				data.enterSound.play();
				if (data.menu.selectedItem == &data.startGameItem)
				{
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.settingsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.difficultyItem)
				{
					ChangeDifficultyLevel(game, event);
					data.difficultyItem.text.setString("Difficulty - " + game.difficultyString);
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
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
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });

		window.draw(data.navigationHintText);
	}

	void ShutDownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		//Nothing to shutdown here
	}

}