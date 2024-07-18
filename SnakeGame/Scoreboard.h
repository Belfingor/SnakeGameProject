#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <unordered_map> 
#include <vector>
#include <string>
#include <utility>


namespace SnakeGame
{

	struct ScoreboardData
	{
		// UI data
		sf::Font font;
		sf::Text scoreboardText;

		std::unordered_map<std::string, int> scoreboardMap;
		std::map<int, std::string> sortedScoreboardMap; // int comes as key so map is sorted by scores 

		//--------------------------------------------------------------------------------
		std::string playerName = "YOU";
		int playerScore = 0;
		//--------------------------------------------------------------------------------
	};


	void InitScoreboard(ScoreboardData& data);
	void SortScoreBoard(ScoreboardData& data);
	void DrawScoreBoard(ScoreboardData& data, sf::RenderWindow& window);
}