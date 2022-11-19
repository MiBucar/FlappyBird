#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <State.h>
#pragma once

class Game
{
public:
	Game();
	int Run();
private:
	void PollEvents();
	void GameEvents();

	bool mIsRunning;

	State mState;

	const int mFPS = 200;
	const int mFrameDelay = 1000 / mFPS;
};

