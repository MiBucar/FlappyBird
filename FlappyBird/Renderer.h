#include <Player.h>
#include <Pipes.h>
#include <Background.h>
#include <Collision.h>
#include <Objects.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <Audio.h>

#pragma once
using namespace::obj;

class Renderer
{
public:
	Renderer(Player* player, Background* background, Pipes* pipes, const int width, const int height);
	~Renderer();

	void RenderGameplay(int score);
	void RenderMenu(int state);
	void RenderDeathScreen(int score, int highScore);
	void RenderScoresScreen(int arr[5]);
	void RenderSettingsScreen(int musicLevel, int soundLevel);
	void PlaySound(int id);
	void ChangeMusicLevel(int lvl);
	void ChangeSoundLevel(int lvl);

	// Getters
	bool IsDead() const{ return mPlayer->IsDead(); };
	SDL_Renderer* GetRenderer() const { return mRenderer; };
private:
	// Functions

	void RenderPlayer(SDL_Texture* texture);
	void RenderPipes();
	void RenderFloor();
	void RenderBackground(BackgroundTextures texture);
	void RenderButton(int btn);
	void RenderScore(int score);
	void RenderAudioLevels(int musicLevel, int type);
	void InitTextures();
	void InitAudio();
	void ClearTextPointers(int id);

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Texture* mPlayerTexture[EMPTYPLY];
	SDL_Texture* mMusicLevelsTexture;
	SDL_Texture* mSoundLevelsTexture;
	SDL_Texture* mPipeTexture;
	SDL_Texture* mPipeDownTexture;
	SDL_Texture* mFloorTexture;
	SDL_Texture* mBackgroundTexture[EMPTYBCKG];
	SDL_Texture* mScreenTexture[EMPTYSCR];
	SDL_Texture* mButtonTexture[EMPTYBTN];
	SDL_Rect mSrc;
	SDL_Rect mPlayerAnimation[6];
	SDL_Rect mAudioLevelAnimation;
	SDL_Point mMousePos;
	TTF_Font* mFont;
	Mix_Chunk* mSound[EMPTYSOUND];
	Mix_Music* mMusic[EMPTYMUSIC];

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
	Audio mAudio;
};

