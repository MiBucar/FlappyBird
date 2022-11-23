#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Player
{
public:
	Player(const int width, const int height);
	~Player();

	void Move(bool gameStarted);
	void Died() { mIsDead = true; };

	// Getters
	const SDL_Rect* GetRect() { return &mRect; };
	const std::string GetFlyingTexture() { return mFlyingTexture; };
	const std::string GetFallingTexture() { return mFallingTexture; };
	const bool IsDead() { return mIsDead; };

private:
	std::string mFlyingTexture;
	std::string mFallingTexture;
	SDL_Rect mRect;
	int mFallSpeed;
	int mJumpHeight;
	bool mIsDead = false;

};

