#include "Pipes.h"

Pipes::Pipes(const int width, const int height) : mWidth(width), mHeight(height)
{
	mTexture = "images//Pipe.png";
	mTextureDown = "images//PipeDown.png";

	mPipeQueue.push_front(CreatePipe());
}

// Functions

void Pipes::Move(int speed)
{
	srand(time(NULL));
	mRandomNum = 120 + (rand() % 620);

	for (int i = 0; i < mPipeQueue.size(); i++) {
		mPipeQueue[i].pipe.x -= speed;
		mPipeQueue[i].pipeDown.x -= speed;
	}

	NewPipe();
	DestroyPipe();
}

// Reset pipes
void Pipes::Start()
{
	if (mPipeQueue.size() > 0) mPipeQueue.clear();
	mPipeQueue.push_front(CreatePipe());
}

void Pipes::NewPipe()
{
	for (int i = 0; i < mPipeQueue.size(); i++) {
		if (mPipeQueue[i].pipe.x == 900) {
			mPipeQueue.push_back(CreatePipe());
		}
	}
}

void Pipes::DestroyPipe()
{
	if (mPipeQueue.front().pipe.x + mPipeQueue.front().pipe.w <= 0) {
		mPipeQueue.pop_front();
	}
}

BothPipes Pipes::CreatePipe()
{
	mRandomNum = 200 + (rand() % 300);

	BothPipes pipe;
	pipe.pipe.x = mWidth;
	pipe.pipe.y = mRandomNum;
	pipe.pipe.h = 720;
	pipe.pipe.w = 70;

	pipe.pipeDown.x = pipe.pipe.x;
	pipe.pipeDown.y = (pipe.pipe.y - 140) - pipe.pipe.h;
	pipe.pipeDown.h = pipe.pipe.h;
	pipe.pipeDown.w = pipe.pipe.w;

	return pipe;
}

