#include "Renderer.h"

Renderer::Renderer() : mWindow(nullptr), mRenderer(nullptr), mSrc{ 0, 0, 0, 0 }, mPlayer(mWidth, mHeight), mStartTime(SDL_GetTicks()), mPipes(mWidth, mHeight), mBackground(mHeight)
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

	mPlayerTexture[FLYING] = IMG_LoadTexture(mRenderer, mPlayer.GetFlyingTexture().c_str());
	mPlayerTexture[FALLING] = IMG_LoadTexture(mRenderer, mPlayer.GetFallingTexture().c_str());
	if (!mPlayerTexture[FALLING]) std::cout << "Texture not loaded";
	mPipeTexture = IMG_LoadTexture(mRenderer, mPipes.GetPipe().c_str());
	mPipeDownTexture = IMG_LoadTexture(mRenderer, mPipes.GetPipeDown().c_str());
	mFloorTexture = IMG_LoadTexture(mRenderer, mBackground.GetFloorTexture().c_str());
	mBackgroundTexture = IMG_LoadTexture(mRenderer, mBackground.GetBackgroundTexture().c_str());
}

Renderer::~Renderer()
{
	SDL_DestroyWindow(mWindow); mWindow = nullptr;
	SDL_DestroyRenderer(mRenderer); mRenderer = nullptr;
}

// Functions

void Renderer::RenderGame()
{
	if (mGameStarted == false || mPlayer.IsDead()) mSpeed = 0;
	else mSpeed = 1;
	// Player Move
	UpdateGameplay();
	// Render
	RenderGameplay();
}

void Renderer::RenderGameplay()
{
	SDL_RenderClear(mRenderer);

	RenderBackground();
	RenderPipes();

	if (mPlayer.IsDead()) RenderPlayer(mPlayerTexture[FALLING]);
	else RenderPlayer(mPlayerTexture[FLYING]);
	
	RenderFloor();

	SDL_RenderPresent(mRenderer);
}

void Renderer::UpdateGameplay()
{
	mPlayer.Move(mGameStarted);
	mPipes.Move(mSpeed);
	mBackground.MoveFloor(mSpeed);

	for (int i = 0; i < mPipes.GetSize(); i++) {
		if (Collision::CheckCollision(mPlayer.GetRect(), mPipes.GetPipeRect(i), mPipes.GetPipeDown(i))) {
			mPlayer.Died();
		};
	}
}

void Renderer::RenderPlayer(SDL_Texture* texture)
{
	int animationLength = 6;
	int animationRate = 5;

	mPlayerAnimation[0].x = 0;
	mPlayerAnimation[0].y = 0;
	mPlayerAnimation[0].h = 50;
	mPlayerAnimation[0].w = 50;

	for (int i = 1; i < 6; i++) {
		mPlayerAnimation[i].x = 50 * i;
		mPlayerAnimation[i].y = 0;
		mPlayerAnimation[i].h = 50;
		mPlayerAnimation[i].w = 50;
	}
	mSrc.w = mPlayer.GetRect()->w;
	mSrc.h = mPlayer.GetRect()->h;

	int frameToDraw = ((SDL_GetTicks() - mStartTime) * animationRate / 1000) % animationLength;
	SDL_RenderCopy(mRenderer, texture, &mPlayerAnimation[frameToDraw], mPlayer.GetRect());
}

void Renderer::RenderPipes()
{
	mSrc.w = mPipes.GetPipeRect(0)->w;
	mSrc.h = mPipes.GetPipeRect(0)->h;

	for (int i = 0; i < mPipes.GetSize(); i++) {
		SDL_RenderCopy(mRenderer, mPipeTexture, &mSrc, mPipes.GetPipeRect(i));

		SDL_RenderCopy(mRenderer, mPipeDownTexture, &mSrc, mPipes.GetPipeDown(i));
	}
}

void Renderer::RenderFloor()
{
	mSrc.w = mBackground.GetFloorRect()->w;
	mSrc.h = mBackground.GetFloorRect()->h;

	SDL_RenderCopy(mRenderer, mFloorTexture, &mSrc, mBackground.GetFloorRect());
}

void Renderer::RenderBackground()
{
	mSrc.w = mBackground.GetBackgroundRect()->w;
	mSrc.h = mBackground.GetBackgroundRect()->h;

	SDL_RenderCopy(mRenderer, mBackgroundTexture, &mSrc, mBackground.GetBackgroundRect());
}
