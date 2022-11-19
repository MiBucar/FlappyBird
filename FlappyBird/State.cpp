#include "State.h"

State::State() : mWindow(nullptr), mRenderer(nullptr), mSrc{ 0, 0, 0, 0 }, mPlayer(mWidth, mHeight), mStartTime(SDL_GetTicks()), mPipes(mWidth, mHeight), mBackground(mHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Failed to init the video: " << SDL_GetError() << "\n";
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "Failed to init the image: " << SDL_GetError() << "\n";
	}
	else {
		mWindow = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, 0);
		if (!mWindow) {
			std::cout << "Failed to create the window: " << SDL_GetError() << "\n";
		}
		mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
		if (!mRenderer) {
			std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
		}
	}

	mPlayerTexture[PLAYER] = IMG_LoadTexture(mRenderer, mPlayer.GetTexture().c_str());
	mPipeTexture = IMG_LoadTexture(mRenderer, mPipes.GetPipe().c_str());
	mPipeDownTexture = IMG_LoadTexture(mRenderer, mPipes.GetPipeDown().c_str());
	mFloorTexture = IMG_LoadTexture(mRenderer, mBackground.GetFloorTexture().c_str());
	mBackgroundTexture = IMG_LoadTexture(mRenderer, mBackground.GetBackgroundTexture().c_str());
}

State::~State()
{
	SDL_DestroyWindow(mWindow); mWindow = nullptr;
	SDL_DestroyRenderer(mRenderer); mRenderer = nullptr;
}

// Functions

void State::Playing()
{
	// Player Move
	UpdateGame();
	// Render
	RenderGame();
}

void State::RenderGame()
{
	SDL_RenderClear(mRenderer);

	RenderBackground();
	RenderPlayer();
	RenderPipes();
	RenderFloor();

	SDL_RenderPresent(mRenderer);
}

void State::UpdateGame()
{
	mPlayer.Move();
	mPipes.Move();
	mBackground.MoveFloor();
}

void State::RenderPlayer()
{
	int animationLength = 6;
	int animationRate = 5;

	mFlayingAnimation[0].x = 0;
	mFlayingAnimation[0].y = 0;
	mFlayingAnimation[0].h = 50;
	mFlayingAnimation[0].w = 50;

	for (int i = 1; i < 6; i++) {
		mFlayingAnimation[i].x = 50 * i;
		mFlayingAnimation[i].y = 0;
		mFlayingAnimation[i].h = 50;
		mFlayingAnimation[i].w = 50;
	}
	mSrc.w = mPlayer.GetRect()->w;
	mSrc.h = mPlayer.GetRect()->h;

	int frameToDraw = ((SDL_GetTicks() - mStartTime) * animationRate / 1000) % animationLength;
	SDL_RenderCopy(mRenderer, mPlayerTexture[PLAYER], &mFlayingAnimation[frameToDraw], mPlayer.GetRect());
}

void State::RenderPipes()
{
	mSrc.w = mPipes.GetPipeOneRect(0)->w;
	mSrc.h = mPipes.GetPipeOneRect(0)->h;

	for (int i = 0; i < mPipes.GetSize(); i++) {
		SDL_RenderCopy(mRenderer, mPipeTexture, &mSrc, mPipes.GetPipeOneRect(i));

		SDL_RenderCopy(mRenderer, mPipeDownTexture, &mSrc, mPipes.GetPipeTwoRect(i));
	}
}

void State::RenderFloor()
{
	mSrc.w = mBackground.GetFloorRect()->w;
	mSrc.h = mBackground.GetFloorRect()->h;

	SDL_RenderCopy(mRenderer, mFloorTexture, &mSrc, mBackground.GetFloorRect());
}

void State::RenderBackground()
{
	mSrc.w = mBackground.GetBackgroundRect()->w;
	mSrc.h = mBackground.GetBackgroundRect()->h;

	SDL_RenderCopy(mRenderer, mBackgroundTexture, &mSrc, mBackground.GetBackgroundRect());
}
