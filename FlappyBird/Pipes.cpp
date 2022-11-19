#include "Pipes.h"

Pipes::Pipes(const int width, const int height) : mWidth(width), mHeight(height)
{
	mTexture = "images//Pipe.png";
	mTextureDown = "images//PipeDown.png";

	mPipeQueue.push_front(CreatePipe());
}

// Functions

void Pipes::Move()
{
	srand(time(NULL));
	mRandomNum = 120 + (rand() % 620);

	for (int i = 0; i < mPipeQueue.size(); i++) {
		mPipeQueue[i].pipeOne.x -= 1;
		mPipeQueue[i].pipeTwo.x -= 1;
	}

	NewPipe();
	DestroyPipe();
}

void Pipes::NewPipe()
{
	for (int i = 0; i < mPipeQueue.size(); i++) {
		if (mPipeQueue[i].pipeOne.x == 900) {
			mPipeQueue.push_back(CreatePipe());
		}
	}
}

void Pipes::DestroyPipe()
{
	if (mPipeQueue.front().pipeOne.x + mPipeQueue.front().pipeOne.w <= 0) {
		mPipeQueue.pop_front();
	}
}

BothPipes Pipes::CreatePipe()
{
	mRandomNum = 200 + (rand() % 300);

	BothPipes pipe;
	pipe.pipeOne.x = mWidth;
	pipe.pipeOne.y = mRandomNum;
	pipe.pipeOne.h = 720;
	pipe.pipeOne.w = 70;

	pipe.pipeTwo.x = pipe.pipeOne.x;
	pipe.pipeTwo.y = (pipe.pipeOne.y - 140) - pipe.pipeOne.h;
	pipe.pipeTwo.h = pipe.pipeOne.h;
	pipe.pipeTwo.w = pipe.pipeOne.w;

	return pipe;
}

