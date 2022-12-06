#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Player
{
public:
	Player(const int width, const int height);

	void Move(bool gameStarted);
	void Start();
	void Block();
	const void Died() { mIsDead = true; };
	const void Alive() { mIsDead = false; };

	// Getters
	const SDL_Rect* GetRect() const{ return &mRect; };
	std::string GetFlyingTexture() const{ return mFlyingTexture; };
	std::string GetFallingTexture() const{ return mFallingTexture; };
	bool IsDead() const{ return mIsDead; };

private:
	std::string mFlyingTexture;
	std::string mFallingTexture;
	SDL_Rect mRect;
	int mFallSpeed;
	int mJumpHeight;
	bool mIsDead = false;

	const int mWidth;
	const int mHeight;
};

