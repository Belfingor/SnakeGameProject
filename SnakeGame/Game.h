#pragma once
#include "Snake.h"
#include "Apple.h"
#include "Math.h"
#include "Constants.h"
#include "Scoreboard.h"

#include <SFML/Graphics.hpp>
#include <vector> 
#include <cassert>
#include <string>


namespace SnakeGame
{
	enum class DifficultyLevelModes : std::uint8_t
	{
		DifficultyLevel1 = 1 << 0,
		DifficultyLevel2 = 1 << 1,
		DifficultyLevel3 = 1 << 2,
		DifficultyLevel4 = 1 << 3,
		DifficultyLevel5 = 1 << 4,

		Default = DifficultyLevel1
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		ExitDialog,
		AddToScoreboard,
		GameOver		
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct Game
	{
		ScoreboardData scoreboardData;
		DifficultyLevelModes difficulty = DifficultyLevelModes::Default;
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool isPendingGameStateExclusivelyVisible = false;

		bool isGameWon = false; // For identifying if game is lost or won;
		int gameScore = 0;
		float gameSpeedModifier = 0.f;
		int gameScoreModifier = 2;
		std::string difficultyString = "Very Easy";
	};

	void ChangeDifficultyLevel(Game& game, const sf::Event event);
	void UpdateDifficultySettings(Game& game);
	void UpdateDifficultyString(Game& game);
	//--------------------------------------------------------------------------------
	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);
	void PopGameState(Game& game);
	void SwitchGameState(Game& game, GameStateType newState);
	//--------------------------------------------------------------------------------

	bool UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutDownGame(Game& game);
	void InitGameState(Game& game, GameState& state);
	void ShutDownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float deltaTime);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);

	//--------------------------------------------------------------------------------
	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	void DeinitializeGame(Game& game);


}