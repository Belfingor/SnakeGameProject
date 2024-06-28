/*This file determines the entire system of how 
Main Menu child/parent logic works for Menu Items*/
#pragma once
#include "Math.h"
#include <list>
#include <SFML/Graphics.hpp>


namespace SnakeGame
{
	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText;
		Orientation childOrientation = Orientation::Vertical;
		Alignment childAlignment = Alignment::Min;
		float childSpacing;

		sf::Color selectedColor = sf::Color::Green;
		sf::Color deselectedColor = sf::Color::White;

		bool isEnabled = true;
		std::vector<MenuItem*> children;

		MenuItem* parent = nullptr;
	};

	struct Menu
	{
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;
	};

	void InitMenuItem(MenuItem& item);
	void SelectMenuItem(Menu& menu, MenuItem* item);
	bool SelectPreviousMenuItem(Menu& menu);
	bool SelectNextMenuItem(Menu& menu);
	bool ExpandSelectedItem(Menu& menu);
	bool CollapseSelectedItem(Menu& menu);
	MenuItem* GetCurrentMenuContext(Menu& menu);
	void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);

}