#include "Game.h"

// Functions

Game::Game() : mPlayer(new Player(mScreenWidth, mScreenHeight)), mPipes(new Pipes(mScreenWidth, mScreenHeight)), mBackground(new Background(mScreenWidth, mScreenHeight)), mRenderer(mPlayer, mBackground, mPipes, mScreenWidth, mScreenHeight), mIsRunning(true), mMousePos{ 0, 0 }
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
		case SDL_MOUSEBUTTONDOWN:
			HandleMouse(event.button);
			break;
		default:
			break;
		}
	}

	int x, y;
	SDL_GetMouseState(&x, &y);
	mMousePos.x = x; mMousePos.y = y;
}

void Game::GameEvents()
{
	SDL_RenderClear(mRenderer.GetRenderer());

	if (mGameStarted) {
		if (!mPlayer->IsDead()) {
			mSpeed = 1;
			Playing();

		}
		else {
			mSpeed = 0;
			Playing();
			Died();
		}
	}
	else {
		Menu();
	}

	SDL_RenderPresent(mRenderer.GetRenderer());
}

void Game::Playing()
{
	mPlayer->Move(mGameStarted);
	mPipes->Move(mSpeed);
	mBackground->MoveFloor(mSpeed);

	for (int i = 0; i < mPipes->GetSize(); i++) {
		if (Collision::CheckCollision(mPlayer->GetRect(), mPipes->GetPipeRect(i), mPipes->GetPipeDown(i))) {
			mPlayer->Died();
		};
	}

	mRenderer.RenderGameplay();
}

void Game::Menu()
{
	mRenderer.RenderMenu();
}

void Game::Died()
{
	mRenderer.RenderDeathScreen();
}


void Game::StartGame()
{
	mPlayer->Alive();
	mPipes->Start();
}

void Game::HandleMouse(SDL_MouseButtonEvent btn)
{
	if (btn.button == SDL_BUTTON_LEFT) {
		if (mGameStarted == false) {
			if (mMousePos.x >= mBackground->GetButtonRect(PLAY)->x && mMousePos.x <= mBackground->GetButtonRect(PLAY)->x + mBackground->GetButtonRect(PLAY)->w &&
				mMousePos.y >= mBackground->GetButtonRect(PLAY)->y && mMousePos.y <= mBackground->GetButtonRect(PLAY)->y + mBackground->GetButtonRect(PLAY)->h) {
				mGameStarted = true;
				StartGame();
			}
		}
		else {
			if (mMousePos.x >= mBackground->GetButtonRect(PLAY_AGAIN)->x && mMousePos.x <= mBackground->GetButtonRect(PLAY_AGAIN)->x + mBackground->GetButtonRect(PLAY_AGAIN)->w &&
				mMousePos.y >= mBackground->GetButtonRect(PLAY_AGAIN)->y && mMousePos.y <= mBackground->GetButtonRect(PLAY_AGAIN)->y + mBackground->GetButtonRect(PLAY_AGAIN)->h) {
				mGameStarted = true;
				StartGame();
			}
		}
	}
}


