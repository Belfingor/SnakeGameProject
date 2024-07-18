#include "scoreboard.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <cassert>


namespace SnakeGame
{
	void InitScoreboard(ScoreboardData& data)
	{
		assert(data.font.loadFromFile("Resources/Fonts/Roboto-BlackItalic.ttf"));
		data.scoreboardText.setFont(data.font);
		data.scoreboardText.setCharacterSize(24);
		data.scoreboardText.setFillColor(sf::Color::White);
		data.scoreboardText.setPosition(SCREEN_HEIGHT /2 , SCREEN_HEIGHT /2);
		data.scoreboardText.setString("Scoreboard:\n");

		data.scoreboardMap =
		{
			{ "Player1", 10 },
			{ "Player2", 6 },
			{ "Player3", 8 },
			{ data.playerName, data.playerScore }
		};

		SortScoreBoard(data);

		std::vector<std::pair<std::string, int>> scoreboardItemPairs(data.scoreboardMap.begin(), data.scoreboardMap.end());
		std::reverse(scoreboardItemPairs.begin(), scoreboardItemPairs.end());
		for (const auto& item : scoreboardItemPairs)
		{
			data.scoreboardText.setString(data.scoreboardText.getString() + item.first + " - " + std::to_string(item.second) + "\n");
		}
	}

	void SortScoreBoard(ScoreboardData& data)
	{
		// Shuffle scoreboatrd maps from unordered_map to map and back to sort the scoreBoard by it's values (scores) and not the keys (Names)
		for (const auto& item : data.scoreboardMap)
		{
			data.sortedScoreboardMap.insert({ item.second, item.first });
		}
		data.scoreboardMap.clear();

		for (const auto& item : data.sortedScoreboardMap)
		{
			data.scoreboardMap.insert({ item.second, item.first });
		}
		data.sortedScoreboardMap.clear();
	}

	void DrawScoreBoard(ScoreboardData& data, sf::RenderWindow& window)
	{
		window.draw(data.scoreboardText);
	}

}