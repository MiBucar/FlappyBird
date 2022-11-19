#include <Player.h>
#include <Pipes.h>
#include <Background.h>
#pragma once

class State
{
public:
	State();
	~State();

	void Playing();
private:
	// Functions
	void RenderGame();
	void UpdateGame();
	void RenderPlayer();
	void RenderPipes();
	void RenderFloor();
	void RenderBackground();

	// Objects
	enum Textures {
		PLAYER,
		EMPTY
	};

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Texture* mPlayerTexture[EMPTY];
	SDL_Texture* mPipeTexture;
	SDL_Texture* mPipeDownTexture;
	SDL_Texture* mFloorTexture;
	SDL_Texture* mBackgroundTexture;
	SDL_Rect mSrc;
	SDL_Rect mFlayingAnimation[6];

	const int mWidth = 1280;
	const int mHeight = 720;
	int mStartTime;

	Player mPlayer;
	Pipes mPipes;
	Background mBackground;
};

