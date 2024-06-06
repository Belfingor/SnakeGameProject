#pragma once
#include "Snake.h"
#include "Apple.h"

namespace SnakeGame
{
	bool DidSnakeCollideWithWall(Snake& snake);
	bool DidSnakeCollideWithApple(Snake& snake, Apple& apple);
	bool DidSnakeCollideWithTail(Snake& snake);
}