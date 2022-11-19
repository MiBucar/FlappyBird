#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Player
{
public:
	Player(const int width, const int height);
	~Player();

	void Move();
	const SDL_Rect* GetRect() { return &mRect; };
	const std::string GetTexture() { return mTexture; };
private:
	std::string mTexture;
	SDL_Rect mRect;
	int mFallSpeed;
	int mJumpHeight;
};

