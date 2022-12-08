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

	std::string GetBackgroundTexture(int id) const { return mBackgroundTexture[id]; };
	const SDL_Rect* GetBackgroundRect() const { return &mBackgroundRect; };

	std::string GetScreenBackground(int scr) const { return mScreenTexture[scr]; };
	const SDL_Rect* GetScreenRect() const { return &mScreenRect; };

	std::string GetButtonTexture(int btn) const { return mButtonTexture[btn]; };
	const SDL_Rect* GetButtonRect(int btn) const { return &mButtonRect[btn]; };

	const SDL_Rect* GetTextRect(int txt) const { return &mTextRect[txt]; };

	void MoveFloor(int speed);
private:
	void InitButton();
	void InitText();

	std::string mFloor;
	std::string mScreenTexture[EMPTYSCR];
	std::string mBackgroundTexture[EMPTYBCKG];
	std::string mButtonTexture[EMPTYBTN];

	SDL_Rect mFloorRect;
	SDL_Rect mScreenRect;
	SDL_Rect mBackgroundRect;
	SDL_Rect mButtonRect[EMPTYBTN];
	SDL_Rect mTextRect[EMPTYTEXT];

	const int mWidth;
	const int mHeight;
};

