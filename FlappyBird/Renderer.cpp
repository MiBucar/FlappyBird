#include "Renderer.h"

Renderer::Renderer(Player* player, Background* background, Pipes* pipes, const int width, const int height) : mPlayer(player), mPipes(pipes), mBackground(background), mWidth(width), mHeight(height), mWindow(nullptr), mRenderer(nullptr), mSrc{ 0, 0, 0, 0 }, mStartTime(SDL_GetTicks()), mMousePos{0, 0} {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Failed to init the video: " << SDL_GetError() << "\n";
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "Failed to init the image: " << SDL_GetError() << "\n";
	}
	if (TTF_Init() == -1) {
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

	mPlayerTexture[PlayerTextures::FLYING] = IMG_LoadTexture(mRenderer, mPlayer->GetFlyingTexture().c_str());
	mPlayerTexture[PlayerTextures::FALLING] = IMG_LoadTexture(mRenderer, mPlayer->GetFallingTexture().c_str());
	mPipeTexture = IMG_LoadTexture(mRenderer, mPipes->GetPipe().c_str());
	mPipeDownTexture = IMG_LoadTexture(mRenderer, mPipes->GetPipeDown().c_str());
	mFloorTexture = IMG_LoadTexture(mRenderer, mBackground->GetFloorTexture().c_str());

	mBackgroundTexture[BackgroundTextures::GAMEPLAY] = IMG_LoadTexture(mRenderer, mBackground->GetBackgroundTexture(BackgroundTextures::GAMEPLAY).c_str());
	mBackgroundTexture[BackgroundTextures::MENU] = IMG_LoadTexture(mRenderer, mBackground->GetBackgroundTexture(BackgroundTextures::MENU).c_str());
	mDeathScreenTexture = IMG_LoadTexture(mRenderer, mBackground->GetDeathScreenBackground().c_str());

	mButtonTexture[Buttons::PLAY] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(Buttons::PLAY).c_str());
	mButtonTexture[Buttons::PLAY_AGAIN] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(Buttons::PLAY_AGAIN).c_str());
	mButtonTexture[Buttons::HOME] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(Buttons::HOME).c_str());
}

Renderer::~Renderer()
{
	SDL_DestroyWindow(mWindow); mWindow = nullptr;
	SDL_DestroyRenderer(mRenderer); mRenderer = nullptr;

	for (int i = 0; i < EMPTYPLY; i++) {
		SDL_DestroyTexture(mPlayerTexture[i]);
		mPlayerTexture[i] = nullptr;
	}

	for (int i = 0; i < EMPTYBCKG; i++) {
		SDL_DestroyTexture(mBackgroundTexture[i]);
		mBackgroundTexture[i] = nullptr;
	}

	for (int i = 0; i < EMPTYBTN; i++) {
		SDL_DestroyTexture(mButtonTexture[i]);
		mButtonTexture[i] = nullptr;
	}

	SDL_DestroyTexture(mPipeTexture); mPipeTexture = nullptr;
	SDL_DestroyTexture(mPipeDownTexture); mPipeDownTexture = nullptr;
	SDL_DestroyTexture(mFloorTexture); mFloorTexture = nullptr;
	SDL_DestroyTexture(mDeathScreenTexture); mDeathScreenTexture = nullptr;
}

// Functions


void Renderer::RenderGameplay()
{
	RenderBackground(GAMEPLAY);
	RenderPipes();

	if (mPlayer->IsDead()) RenderPlayer(mPlayerTexture[FALLING]);
	else RenderPlayer(mPlayerTexture[FLYING]);
	
	RenderFloor();
}

void Renderer::RenderMenu()
{

	RenderBackground(MENU);
	RenderFloor();
	RenderButtons();

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

	mSrc.w = mPlayer->GetRect()->w;
	mSrc.w = mPlayer->GetRect()->h;

	int frameToDraw = ((SDL_GetTicks() - mStartTime) * animationRate / 1000) % animationLength;
	SDL_RenderCopy(mRenderer, texture, &mPlayerAnimation[frameToDraw], mPlayer->GetRect());
}

void Renderer::RenderPipes()
{
	mSrc.w = mPipes->GetPipeRect(0)->w;
	mSrc.h = mPipes->GetPipeRect(0)->h;

	for (int i = 0; i < mPipes->GetSize(); i++) {
		SDL_RenderCopy(mRenderer, mPipeTexture, &mSrc, mPipes->GetPipeRect(i));

		SDL_RenderCopy(mRenderer, mPipeDownTexture, &mSrc, mPipes->GetPipeDown(i));
	}
}

void Renderer::RenderFloor()
{
	mSrc.w = mBackground->GetFloorRect()->w;
	mSrc.h = mBackground->GetFloorRect()->h;

	SDL_RenderCopy(mRenderer, mFloorTexture, &mSrc, mBackground->GetFloorRect());
}

void Renderer::RenderBackground(BackgroundTextures texture)
{
	mSrc.w = mBackground->GetBackgroundRect()->w;
	mSrc.h = mBackground->GetBackgroundRect()->h;

	SDL_RenderCopy(mRenderer, mBackgroundTexture[texture], &mSrc, mBackground->GetBackgroundRect());
}

void Renderer::RenderButtons()
{
	mSrc.w = mBackground->GetButtonRect(PLAY)->w;
	mSrc.h = mBackground->GetButtonRect(PLAY)->h;

	SDL_RenderCopy(mRenderer, mButtonTexture[PLAY], &mSrc, mBackground->GetButtonRect(PLAY));
}

void Renderer::RenderDeathScreen()
{
	mSrc.w = mBackground->GetDeathScreenRect()->w;
	mSrc.h = mBackground->GetDeathScreenRect()->h;

	SDL_RenderCopy(mRenderer, mDeathScreenTexture, &mSrc, mBackground->GetDeathScreenRect());

	mSrc.w = mBackground->GetButtonRect(PLAY_AGAIN)->w;
	mSrc.h = mBackground->GetButtonRect(PLAY_AGAIN)->h;
	SDL_RenderCopy(mRenderer, mButtonTexture[PLAY_AGAIN], &mSrc, mBackground->GetButtonRect(PLAY_AGAIN));

	mSrc.w = mBackground->GetButtonRect(HOME)->w;
	mSrc.h = mBackground->GetButtonRect(HOME)->h;
	SDL_RenderCopy(mRenderer, mButtonTexture[HOME], &mSrc, mBackground->GetButtonRect(HOME));
}

