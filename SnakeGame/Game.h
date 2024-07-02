#pragma once
#include "Snake.h"
#include "Apple.h"
#include "Math.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <vector> 
#include <cassert>


namespace SnakeGame
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		ExitDialog,
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
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool isPendingGameStateExclusivelyVisible = false;
	};

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