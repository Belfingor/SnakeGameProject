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
		std::string playerName;
		int playerScore = 0;
		//--------------------------------------------------------------------------------
	};


	void InitScoreboard(ScoreboardData& data);
	void UpdateScoreboardText(ScoreboardData& data);
	bool SerializeScoreboard(ScoreboardData& data);
	bool DeserializeScoreboard(ScoreboardData& data);
	void AddPlayerScoreToScoreboard(ScoreboardData& data);
	std::string ScoreboardHandleInputEvents(ScoreboardData& data, const sf::Event& event);
	void SortScoreBoard(ScoreboardData& data);
}