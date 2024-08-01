#include "scoreboard.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <fstream>
#include <algorithm>


namespace SnakeGame
{
	void InitScoreboard(ScoreboardData& data)
	{
		assert(data.font.loadFromFile("Resources/Fonts/Roboto-BlackItalic.ttf"));
		data.scoreboardText.setFont(data.font);
		data.scoreboardText.setCharacterSize(24);
		data.scoreboardText.setFillColor(sf::Color::White);
		data.scoreboardText.setPosition(50 , SCREEN_HEIGHT /2.5);
	}

	void UpdateScoreboardText(ScoreboardData& data, int sizeLimit, bool isInMainMenu)
	{
		if (isInMainMenu == true)
		{
			data.scoreboardText.setString("");
		}
		else
		{
			data.scoreboardText.setString("Scoreboard:\n");
		}
		DeserializeScoreboard(data);
		std::reverse(data.scoreboardV.begin(), data.scoreboardV.end());
		int count = 0;

		for (const auto& item : data.scoreboardV)
		{
			if (count == sizeLimit)
			{
				break;
			}
			data.scoreboardText.setString(data.scoreboardText.getString() + item.first + " - " + std::to_string(item.second) + "\n");
			count++;
		}
	}

	bool SerializeScoreboard(ScoreboardData& data) // Rewrite Scoreboard File data
	{
		std::ofstream file(SCOREBOARD_FILE_PATH);
		if (file.is_open())
		{
			for (const auto& record : data.scoreboardV)
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
			data.scoreboardV.clear();
			std::string name;
			int score;
			
			while (file >> name >> score)
			{
				data.scoreboardV.emplace_back(name, score);
			}
			file.close();
			return true;
		}
	}

	void AddPlayerScoreToScoreboard(ScoreboardData& data)
	{
		if (!IsPlayerNameAlreadyExists(data))
		{
			data.scoreboardV.push_back(std::pair<std::string, int>(data.playerName, data.playerScore));
			SerializeScoreboard(data);
			SortScoreBoard(data);
		}
		else
		{
			SerializeScoreboard(data);
			SortScoreBoard(data);
		}
	}

	std::string ScoreboardHandleInputEvents(ScoreboardData& data, const sf::Event& event)
	{
		if (event.text.unicode < 128 && event.text.unicode != ' ') // Handle only ASCII characters
		{
			if (event.text.unicode == '\b') // Handling backspace 
			{
				if (!data.playerName.empty())
				{
					data.playerName.pop_back();
				}
			}
			else if (event.text.unicode == 13) // Handling Enter key press 
			{
				//we need to empty player's name, so player can type it again without earsing next time
				data.playerName = "";
			}
			else
			{
				data.playerName += static_cast<char>(event.text.unicode);
			}
		}
		return data.playerName;
	}

	void SortScoreBoard(ScoreboardData& data)
	{
		DeserializeScoreboard(data);

		for (const auto& item : data.scoreboardV)
		{
			data.sortedScoreboardMap.insert({ item.second, item.first });
		}
		data.scoreboardV.clear();

		for (const auto& item : data.sortedScoreboardMap)
		{
			data.scoreboardV.push_back({ item.second, item.first });
		}

		data.sortedScoreboardMap.clear();
		SerializeScoreboard(data);
	}

	bool IsPlayerNameAlreadyExists(ScoreboardData& data)
	{
		for (auto& pair : data.scoreboardV)
		{
			if (pair.first == data.playerName)
			{
				if (pair.second < data.playerScore)
				{
					pair.second = data.playerScore;
				}
				return true;
			}
		}
		return false;
	}
}