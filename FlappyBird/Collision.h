#pragma once
#include <SDL.h>
#include <iostream>

class Collision
{
public:
	static bool CheckPipeCollision(const SDL_Rect *playerRect, const SDL_Rect *pipeRect, const SDL_Rect *pipeDownRect);
	static bool CheckFloorCollision(const SDL_Rect* playerRect, const int height);
	static bool CheckCeilingCollision(const SDL_Rect* playerRect);
};

