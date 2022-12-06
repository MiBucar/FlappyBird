#include <Player.h>
#include <Pipes.h>
#include <Background.h>
#include <Collision.h>
#include <Objects.h>
#include <SDL_ttf.h>
#include <string>
#pragma once
using namespace::obj;

class Renderer
{
public:
	Renderer(Player* player, Background* background, Pipes* pipes, const int width, const int height);
	~Renderer();

	void RenderGameplay(int score);
	void RenderMenu();
	void RenderDeathScreen(int score, int highScore);

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
	void RenderText(int score);

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

	std::string mText[EMPTYTEXT];
	SDL_Surface* mTextSurface[EMPTYTEXT];
	SDL_Texture* mTextTexture[EMPTYTEXT];

	SDL_Color mColorBrown;

	int mStartTime;

	const int mWidth;
	const int mHeight;

	Player *mPlayer;
	Pipes *mPipes;
	Background *mBackground;
};

