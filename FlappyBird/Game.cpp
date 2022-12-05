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

	CheckCollisions();

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
	mPlayer->Start();
	mPipes->Start();
}

void Game::HandleMouse(SDL_MouseButtonEvent btn)
{
	if (btn.button == SDL_BUTTON_LEFT) {
		if (mGameStarted == false) {
			if (CheckMousePos(PLAY)) {
				mGameStarted = true;
				StartGame();
			}
		}
		else {
			if (CheckMousePos(PLAY_AGAIN)) {
				mGameStarted = true;
				StartGame();
			}
			else if (CheckMousePos(HOME)) {
				mGameStarted = false;
			}
		}
	}
}

void Game::CheckCollisions()
{
	for (int i = 0; i < mPipes->GetSize(); i++) {
		if (Collision::CheckPipeCollision(mPlayer->GetRect(), mPipes->GetPipeRect(i), mPipes->GetPipeDown(i))) {
			mPlayer->Died();
		};
	}

	if (Collision::CheckFloorCollision(mPlayer->GetRect(), mScreenHeight)) {
		mPlayer->Died();
	};

	if (Collision::CheckCeilingCollision(mPlayer->GetRect())) {
		mPlayer->Block();
	}
}

// Check if mouse position is within the button position
bool Game::CheckMousePos(int btn)
{
	if (mMousePos.x >= mBackground->GetButtonRect(btn)->x && mMousePos.x <= mBackground->GetButtonRect(btn)->x + mBackground->GetButtonRect(btn)->w &&
		mMousePos.y >= mBackground->GetButtonRect(btn)->y && mMousePos.y <= mBackground->GetButtonRect(btn)->y + mBackground->GetButtonRect(btn)->h) {
		return true;
	}

	return false;
}


