#include "Game.h"

// Functions

Game::Game() : mIsRunning(true)
{
}

int Game::Run()
{
	Uint32 frameStart;
	int frameTime;

	while (mIsRunning) {
		frameStart = SDL_GetTicks();

		PollEvents();
		GameEvents();

		frameTime = SDL_GetTicks() - frameStart;

		if (mFrameDelay > frameTime) {
			SDL_Delay(mFrameDelay - frameTime);
		}
	}
	return 0;
}

void Game::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::GameEvents()
{
	mState.Playing();
}


