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
	void Move(int speed);
	void Start();

	// Getters
	std::string GetPipe() const{ return mTexture; };
	std::string GetPipeDown() const { return mTextureDown; };
	int GetSize() const { return static_cast<int>(mPipeQueue.size()); };
	const SDL_Rect *GetPipeRect(int index) const { return &mPipeQueue[index].pipe; };
	const SDL_Rect *GetPipeDown(int index) const { return &mPipeQueue[index].pipeDown; };
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

