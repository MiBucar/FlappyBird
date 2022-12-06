#include <Player.h>
#include <Pipes.h>
#include <Background.h>
#include <Collision.h>
#include <Objects.h>
#include <SDL_ttf.h>
#pragma once
using namespace::obj;

class Renderer
{
public:
	Renderer(Player* player, Background* background, Pipes* pipes, const int width, const int height);
	~Renderer();

	void RenderGameplay();
	void RenderMenu();
	void RenderDeathScreen();

	// Getters
	bool IsDead() const{ return mPlayer->IsDead(); };
	SDL_Renderer* GetRenderer() const { return mRenderer; };
private:
	// Functions

	void RenderPlayer(SDL_Texture* texture);
	void RenderPipes();
	void RenderFloor();
	void RenderBackground(BackgroundTextures texture);
	void RenderButtons();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Texture* mPlayerTexture[EMPTYPLY];
	SDL_Texture* mPipeTexture;
	SDL_Texture* mPipeDownTexture;
	SDL_Texture* mFloorTexture;
	SDL_Texture* mBackgroundTexture[EMPTYBCKG];
	SDL_Texture* mDeathScreenTexture;
	SDL_Texture* mButtonTexture[EMPTYBTN];
	SDL_Rect mSrc;
	SDL_Rect mPlayerAnimation[6];
	SDL_Point mMousePos;
	TTF_Font* mFont;

	int mStartTime;

	const int mWidth;
	const int mHeight;

	Player *mPlayer;
	Pipes *mPipes;
	Background *mBackground;
};

