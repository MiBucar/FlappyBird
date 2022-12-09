#include "Game.h"

// Functions

Game::Game() : mPlayer(new Player(mScreenWidth, mScreenHeight)), mPipes(new Pipes(mScreenWidth, mScreenHeight)),
mBackground(new Background(mScreenWidth, mScreenHeight)), mRenderer(mPlayer, mBackground, mPipes, mScreenWidth, mScreenHeight),
mIsRunning(true), mMousePos{ 0, 0 }
{
}

Game::~Game()
{
	delete mPlayer;
	delete mPipes;
	delete mBackground;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
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

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE]) mOpenLeaderboard = false;

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
		if (!mOpenLeaderboard) {
			Menu();
		}
		else {
			Menu();
			Leaderboard();
		}
	}

	SDL_RenderPresent(mRenderer.GetRenderer());
}

void Game::Playing()
{
	mPlayer->Move(mGameStarted);
	mPipes->Move(mSpeed);
	mBackground->MoveFloor(mSpeed);

	CheckCollisions();

	mRenderer.RenderGameplay(mScore);
}

void Game::Menu()
{
	mRenderer.RenderMenu();
}

void Game::Leaderboard()
{
	int arr[5];
	for (int i = 0; i < 5; i++) {
		arr[i] = mData.GetTopFiveScores().at(mData.GetTopFiveScores().size() - (i + 1));
	}
	mRenderer.RenderScoresScreen(arr);
}

void Game::Died()
{
	if (mAddScore) mData.AddScore(mScore);
	mAddScore = false;

	mRenderer.RenderDeathScreen(mScore, mData.GetHighScore());
}


void Game::StartGame()
{
	mPlayer->Alive();
	mPlayer->Start();
	mPipes->Start();
	mScore = 0;
	mAddScore = true;
}

void Game::HandleMouse(SDL_MouseButtonEvent btn)
{
	if (btn.button == SDL_BUTTON_LEFT) {
		if (mGameStarted == false) {
			if (CheckMousePos(BTNPLAY)) {
				mGameStarted = true;
				StartGame();
			}
			else if (CheckMousePos(BTNSCORE)) {
				mOpenLeaderboard = true;
			}
		}
		else {
			if (mOpenLeaderboard == true) {
				if (CheckMousePos(BTNRESETSCORE)) {
					mData.RestartScores();
				}
			}
			else {
				if (CheckMousePos(BTNPLAY_AGAIN)) {
					mGameStarted = true;
					StartGame();
				}
				else if (CheckMousePos(BTNHOME)) {
					mGameStarted = false;
				}
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

	for (int i = 0; i < mPipes->GetSize(); i++) {
		if (Collision::CheckForScoreUpdate(mPlayer->GetRect(), mPipes->GetPipeRect(i))) {
			mScore += 1;
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


