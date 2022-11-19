#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Background
{
public:
	Background(int height);

	// Getters
	const std::string GetFloorTexture() { return mFloor; };
	const SDL_Rect* GetFloorRect() { return &mFloorRect; };

	const std::string GetBackgroundTexture() { return mBackground; };
	const SDL_Rect* GetBackgroundRect() { return &mBackgroundRect; };

	void MoveFloor();
private:
	const std::string mFloor;
	const std::string mBackground;
	SDL_Rect mFloorRect;
	SDL_Rect mBackgroundRect;
};

