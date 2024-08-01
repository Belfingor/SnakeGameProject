#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include <utility>


namespace SnakeGame
{

	struct ScoreboardData
	{
		sf::Font font;
		sf::Text scoreboardText;

		std::multimap<int, std::string> sortedScoreboardMap; // int comes as key so map is sorted by scores 
		std::vector<std::pair<std::string, int>> scoreboardV;

		std::string playerName;
		int playerScore = 0;
	};


	void InitScoreboard(ScoreboardData& data);
	void UpdateScoreboardText(ScoreboardData& data, int sizeLimit, bool isInMainMenu);
	bool SerializeScoreboard(ScoreboardData& data);
	bool DeserializeScoreboard(ScoreboardData& data);
	void AddPlayerScoreToScoreboard(ScoreboardData& data);
	std::string ScoreboardHandleInputEvents(ScoreboardData& data, const sf::Event& event);
	void SortScoreBoard(ScoreboardData& data);
	bool IsPlayerNameAlreadyExists(ScoreboardData& data);
}