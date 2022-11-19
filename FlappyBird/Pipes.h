#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <deque>
#include <stdlib.h>
#include <time.h>

struct BothPipes {
	SDL_Rect pipeOne;
	SDL_Rect pipeTwo;
};

class Pipes
{
public:
	Pipes(const int width, const int height);
	void Move();

	// Getters
	const std::string GetPipe() { return mTexture; };
	const std::string GetPipeDown() { return mTextureDown; };
	const int GetSize() { return mPipeQueue.size(); };
	const SDL_Rect *GetPipeOneRect(int index) { return &mPipeQueue[index].pipeOne; };
	const SDL_Rect *GetPipeTwoRect(int index) { return &mPipeQueue[index].pipeTwo; };
private:
	void NewPipe();
	void DestroyPipe();
	BothPipes CreatePipe();

	std::string mTexture;
	std::string mTextureDown;

	const int mWidth;
	const int mHeight;

	int mRandomNum;

	std::deque<BothPipes> mPipeQueue;
};

