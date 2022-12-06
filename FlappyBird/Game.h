#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <Renderer.h>
#include <Player.h>
#include <Pipes.h>
#include <Background.h>
#include <Data.h>
#pragma once

class Game
{
public:
	Game();
	int Run();
private:
	void PollEvents();
	void GameEvents();
	void StartGame();
	void HandleMouse(SDL_MouseButtonEvent btn);
	void CheckCollisions();
	bool CheckMousePos(int btn);

	// Game States
	void Playing();
	void Died();
	void Menu();

	bool mIsRunning;

	const int mScreenWidth = 1280;
	const int mScreenHeight = 720;

	Data mData;
	Player *mPlayer;
	Pipes *mPipes;
	Background *mBackground;
	Renderer mRenderer;

	SDL_Point mMousePos;

	const int mFPS = 200;
	const int mFrameDelay = 1000 / mFPS;

	int mSpeed = 0;
	bool mGameStarted = false;
};

