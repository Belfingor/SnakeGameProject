#include "Game.h"
#include <cassert>

#include "GameStatePlaying.h"
#include "GameStateMainMenu.h"
#include "GameStateExitDialog.h"
#include "GameStateGameOver.h"


namespace SnakeGame
{
	//-------------------------------------------------------------------------------- GAME DIFFICULTY BITMASK
	void ChangeDifficultyLevel(Game& game, const sf::Event event)
	{
		switch (game.difficulty)
		{
		case DifficultyLevelModes::DifficultyLevel1:
			game.difficulty = DifficultyLevelModes::DifficultyLevel2;
			break;
		case DifficultyLevelModes::DifficultyLevel2:
			game.difficulty = DifficultyLevelModes::DifficultyLevel3;
			break;
		case DifficultyLevelModes::DifficultyLevel3:
			game.difficulty = DifficultyLevelModes::DifficultyLevel4;
			break;
		case DifficultyLevelModes::DifficultyLevel4:
			game.difficulty = DifficultyLevelModes::DifficultyLevel5;
			break;
		case DifficultyLevelModes::DifficultyLevel5:
			game.difficulty = DifficultyLevelModes::DifficultyLevel1;
			break;
		}
		UpdateDifficultySettings(game);
		UpdateDifficultyString(game);
	}
	void UpdateDifficultySettings(Game& game)
	{
		switch (game.difficulty)
		{
		case DifficultyLevelModes::DifficultyLevel1:
			game.gameSpeedModifier = .04f;
			game.gameScoreModifier = 2;
			break;
		case DifficultyLevelModes::DifficultyLevel2:
			game.gameSpeedModifier = .07f;
			game.gameScoreModifier = 4;
			break;
		case DifficultyLevelModes::DifficultyLevel3:
			game.gameSpeedModifier = .12f;
			game.gameScoreModifier = 6;
			break;
		case DifficultyLevelModes::DifficultyLevel4:
			game.gameSpeedModifier = .17f;
			game.gameScoreModifier = 8;
			break;
		case DifficultyLevelModes::DifficultyLevel5:
			game.gameSpeedModifier = .20f;
			game.gameScoreModifier = 10;
			break;
		}
	}
	void UpdateDifficultyString(Game& game)
	{
		switch (game.difficulty)
		{
		case (DifficultyLevelModes::DifficultyLevel1):
			game.difficultyString = "Very Easy";
			break;
		case (DifficultyLevelModes::DifficultyLevel2):
			game.difficultyString = "Easy";
			break;
		case (DifficultyLevelModes::DifficultyLevel3):
			game.difficultyString = "Medium";
			break;
		case (DifficultyLevelModes::DifficultyLevel4):
			game.difficultyString = "Hard";
			break;
		case (DifficultyLevelModes::DifficultyLevel5):
			game.difficultyString = "Very Hard";
			break;
		}
	}
	//--------------------------------------------------------//GAME STATE STACK LOGIC//
	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible)
	{
		game.pendingGameStateType = stateType;
		game.isPendingGameStateExclusivelyVisible = isExclusivelyVisible;
		game.gameStateChangeType = GameStateChangeType::Push;
	}

	void PopGameState(Game& game)
	{
		game.pendingGameStateType = GameStateType::None;
		game.isPendingGameStateExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Pop;
	}

	void SwitchGameState(Game& game, GameStateType newState)
	{
		game.pendingGameStateType = newState;
		game.isPendingGameStateExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Switch;
	}
//--------------------------------------------------------------------------------
	bool UpdateGame(Game& game, float deltaTime)
	{
		if (game.gameStateChangeType == GameStateChangeType::Switch)
		{
			while (game.gameStateStack.size() > 0)
			{
				ShutDownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		else if (game.gameStateChangeType == GameStateChangeType::Pop)
		{
			if (game.gameStateStack.size() > 0)
			{
				ShutDownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}
		if (game.pendingGameStateType != GameStateType::None)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType, nullptr, game.isPendingGameStateExclusivelyVisible });
			InitGameState(game, game.gameStateStack.back());
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.isPendingGameStateExclusivelyVisible = false;

		if (game.gameStateStack.size() > 0)
		{
			UpdateGameState(game, game.gameStateStack.back(), deltaTime);
			return true;
		}
		return false;
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = game.gameStateStack.rbegin(); it != game.gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(game, **it, window);
			}
		}
	}

	void ShutDownGame(Game& game)
	{
		// ShutDown ALL game states
		while (game.gameStateStack.size() > 0)
		{
			ShutDownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.isPendingGameStateExclusivelyVisible = false;
	}

	void InitGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case GameStateType::Playing:
		{
			state.data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data = new GameStateExitDialogData();
			InitGameStateExitDialog(*(GameStateExitDialogData*)state.data, game);
			break;
		}
		case GameStateType::GameOver:
		{
			state.data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		default:
			assert(false); // To make sure every Game State was implemented
			break;
		}
	}

	void ShutDownGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			ShutDownGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			delete (GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			ShutDownGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			delete (GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			ShutDownGameStateExitDialog(*(GameStateExitDialogData*)state.data, game);
			delete (GameStateExitDialogData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			ShutDownGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			delete (GameStateGameOverData*)state.data;
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
			break;
		}
		case GameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, game, event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			HandleGameStateExitDialogWindowEvent(*(GameStateExitDialogData*)state.data, game, event);
			break;
		}
		case GameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void UpdateGameState(Game& game, GameState& state, float deltaTime) //check if i need delta time here later
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::ExitDialog:
		{
			UpdateGameStateExitDialog(*(GameStateExitDialogData*)state.data, game, deltaTime);
			break;
		}
		case GameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game, deltaTime);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
			break;
		}
		case GameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data, game, window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			DrawGameStateExitDialog(*(GameStateExitDialogData*)state.data, game, window);
			break;
		}
		case GameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void InitGame(Game& game)
	{
		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.isPendingGameStateExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::MainMenu);

		//determine background setting here maybe? but define background rectangle in game struct first
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		// Read Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event);
			}
		}
	}

	void DeinitializeGame(Game& game)
	{
		while (game.gameStateStack.size() > 0)
		{
			ShutDownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.isPendingGameStateExclusivelyVisible = false;
	}

}