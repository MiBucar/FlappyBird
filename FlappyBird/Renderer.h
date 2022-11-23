#include <Player.h>
#include <Pipes.h>
#include <Background.h>
#include <Collision.h>
#pragma once

class Renderer
{
public:
	Renderer();
	~Renderer();

	void RenderGame();
	const void SetActive() { mGameStarted = true; };
	const void SetInactive() { mGameStarted = false; };

	// Getters
	const bool IsDead() { return mPlayer.IsDead(); };
private:
	// Functions
	void RenderGameplay();
	void UpdateGameplay();
	void RenderPlayer(SDL_Texture* texture);
	void RenderPipes();
	void RenderFloor();
	void RenderBackground();

	// Objects
	enum Textures {
		FLYING,
		FALLING,
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
	SDL_Rect mPlayerAnimation[6];

	const int mWidth = 1280;
	const int mHeight = 720;
	int mStartTime;

	Player mPlayer;
	Pipes mPipes;
	Background mBackground;
	bool mGameStarted = false;
	float mSpeed = 0;
};

