#pragma once
#include <SDL.h>
#include <iostream>

class Collision
{
public:
	static bool CheckCollision(const SDL_Rect *playerRect, const SDL_Rect *pipeRect, const SDL_Rect *pipeDownRect);
private:
};

