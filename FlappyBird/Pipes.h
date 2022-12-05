#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <deque>
#include <stdlib.h>
#include <time.h>

struct BothPipes {
	SDL_Rect pipe;
	SDL_Rect pipeDown;
};

class Pipes
{
public:
	Pipes(const int width, const int height);
	void Move(float speed);
	void Start();

	// Getters
	const std::string GetPipe() { return mTexture; };
	const std::string GetPipeDown() { return mTextureDown; };
	const int GetSize() { return mPipeQueue.size(); };
	const SDL_Rect *GetPipeRect(int index) { return &mPipeQueue[index].pipe; };
	const SDL_Rect *GetPipeDown(int index) { return &mPipeQueue[index].pipeDown; };
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

