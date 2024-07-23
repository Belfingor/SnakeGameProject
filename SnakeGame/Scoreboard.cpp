#include "scoreboard.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <fstream>


namespace SnakeGame
{
	void InitScoreboard(ScoreboardData& data)
	{
		assert(data.font.loadFromFile("Resources/Fonts/Roboto-BlackItalic.ttf"));
		data.scoreboardText.setFont(data.font);
		data.scoreboardText.setCharacterSize(24);
		data.scoreboardText.setFillColor(sf::Color::White);
		data.scoreboardText.setPosition(40 , SCREEN_HEIGHT /3);

		UpdateScoreboardText(data);
	}

	void UpdateScoreboardText(ScoreboardData& data)
	{
		data.scoreboardText.setString("Scoreboard:\n");
		DeserializeScoreboard(data);
		std::vector<std::pair<std::string, int>> scoreboardItemPairs(data.scoreboardMap.begin(), data.scoreboardMap.end());
		std::reverse(scoreboardItemPairs.begin(), scoreboardItemPairs.end());
		for (const auto& item : scoreboardItemPairs)
		{
			data.scoreboardText.setString(data.scoreboardText.getString() + item.first + " - " + std::to_string(item.second) + "\n");
		}
	}

	bool SerializeScoreboard(ScoreboardData& data) // Rewrite Scoreboard File data
	{
		std::ofstream file(SCOREBOARD_FILE_PATH);
		if (file.is_open())
		{
			for (const auto& record : data.scoreboardMap)
			{
				file << record.first << " " << record.second << std::endl;
			}
			file.close();
			return true;
		}
	}

	bool DeserializeScoreboard(ScoreboardData& data) // Read data from Scoreboard file
	{
		std::ifstream file(SCOREBOARD_FILE_PATH);
		if (file.is_open())
		{
			std::string name;
			int score;
			while (file >> name >> score)
			{
				data.scoreboardMap[name] = score;
			}
			file.close();
			return true;
		}
	}

	void AddPlayerScoreToScoreboard(ScoreboardData& data)
	{
		data.scoreboardMap.insert(std::pair<std::string, int>(data.playerName, data.playerScore));
		SortScoreBoard(data);
	}

	std::string ScoreboardHandleInputEvents(ScoreboardData& data, const sf::Event& event)
	{
		// make sure there is a condition (event.type == sf::Event::TextEntered) when calling this function
		if (event.text.unicode < 128 && event.text.unicode != ' ') // Handle only ASCII characters
		{
			if (event.text.unicode == '\b') // Handling backspace 
			{
				if (!data.playerName.empty())
				{
					data.playerName.pop_back();
				}
			}
			else if (event.text.unicode == 13) // Handleing Enter key press 
			{
				//we need to empty player's name, so player type it again next time
				data.playerName = "";
			}
			else
			{
				data.playerName += static_cast<char>(event.text.unicode); // converting char to string and adding it to players name input string
			}
		}
		return data.playerName;
	}

	void SortScoreBoard(ScoreboardData& data)
	{
		DeserializeScoreboard(data);
		// Shuffle scoreboatrd maps from unordered_map to map and back to sort the scoreBoard by it's values (scores) and not the keys (Names)
		for (const auto& item : data.scoreboardMap)
		{
 			data.sortedScoreboardMap.insert({ item.second, item.first });
		}
		data.scoreboardMap.clear();
		SerializeScoreboard(data);

		for (const auto& item : data.sortedScoreboardMap)
		{
			data.scoreboardMap.insert({ item.second, item.first });
		}
		data.sortedScoreboardMap.clear();
		SerializeScoreboard(data);
	}

}