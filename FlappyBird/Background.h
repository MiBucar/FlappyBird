#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <Objects.h>
using namespace::obj;

class Background
{
public:
	Background(int width, int height);

	// Getters
	std::string GetFloorTexture() const { return mFloor; };
	const SDL_Rect* GetFloorRect() const { return &mFloorRect; };

	std::string GetBackgroundTexture(int id) const { return mBackground[id]; };
	const SDL_Rect* GetBackgroundRect() const { return &mBackgroundRect; };

	std::string GetDeathScreenBackground() const { return mDeathScreen; };
	const SDL_Rect* GetDeathScreenRect() const { return &mDeathScreenRect; };

	std::string GetButtonTexture(int btn) const { return mButton[btn]; };
	const SDL_Rect* GetButtonRect(int btn) const { return &mButtonRect[btn]; };

	const SDL_Rect* GetTextRect(int txt) const { return &mTextRect[txt]; };

	void MoveFloor(int speed);
private:
	std::string mFloor;
	std::string mDeathScreen;
	std::string mBackground[EMPTYBCKG];
	std::string mButton[EMPTYBTN];

	SDL_Rect mFloorRect;
	SDL_Rect mDeathScreenRect;
	SDL_Rect mBackgroundRect;
	SDL_Rect mButtonRect[EMPTYBTN];
	SDL_Rect mTextRect[EMPTYTEXT];

	const int mWidth;
	const int mHeight;
};

