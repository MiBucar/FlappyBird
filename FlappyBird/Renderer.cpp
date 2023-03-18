#include "Renderer.h"

Renderer::Renderer(Player* player, Background* background, Pipes* pipes, const int width, const int height) : mPlayer(player), mPipes(pipes), mBackground(background), mWidth(width), mHeight(height), mWindow(nullptr), mRenderer(nullptr), mSrc{ 0, 0, 0, 0 }, mStartTime(SDL_GetTicks()), mMousePos{0, 0}, mAudio(mWidth, mHeight){

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cout << "Failed to init the video/audio: " << SDL_GetError() << "\n";
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "Failed to init the image: " << SDL_GetError() << "\n";
	}
	if (TTF_Init() == -1) {
		std::cout << "Failed to init the image: " << SDL_GetError() << "\n";
	}
	if (Mix_OpenAudio(4410, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Failed to init the mixer: " << SDL_GetError() << "\n";
	}
	else {
		mWindow = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, 0);
		if (!mWindow) {
			std::cout << "Failed to create the window: " << SDL_GetError() << "\n";
		}
		mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
		if (!mRenderer) {
			std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
		}
		mFont = TTF_OpenFont("font//PixelGosub.ttf", 28);
		if (!mFont) {
			std::cout << "Failed to create the font: " << SDL_GetError() << "\n";
		}
	}

	mColorBrown = { 181, 127, 102 };
	InitTextures();
	InitAudio();
}

Renderer::~Renderer()
{
	SDL_DestroyWindow(mWindow); mWindow = nullptr;
	SDL_DestroyRenderer(mRenderer); mRenderer = nullptr;

	for (int i = 0; i < EMPTYPLY; i++) {
		SDL_DestroyTexture(mPlayerTexture[i]); mPlayerTexture[i] = nullptr;
	}

	for (int i = 0; i < EMPTYBCKG; i++) {
		SDL_DestroyTexture(mBackgroundTexture[i]); mBackgroundTexture[i] = nullptr;
	}

	for (int i = 0; i < EMPTYBTN; i++) {
		SDL_DestroyTexture(mButtonTexture[i]); mButtonTexture[i] = nullptr;
	}

	for (int i = 0; i < EMPTYSCR; i++) {
		SDL_DestroyTexture(mScreenTexture[i]); mScreenTexture[i] = nullptr;
	}

	for (int i = 0; i < EMPTYTEXT; i++) {
		SDL_FreeSurface(mTextSurface[i]); mTextSurface[i] = nullptr;
		SDL_DestroyTexture(mTextTexture[i]); mTextTexture[i] = nullptr;
	}

	for (int i = 0; i < EMPTYSOUND; i++) {
		Mix_FreeChunk(mSound[i]); mSound[i] = nullptr;
	}

	for (int i = 0; i < EMPTYMUSIC; i++) {
		Mix_FreeMusic(mMusic[i]); mMusic[i] = nullptr;
	}

	SDL_DestroyTexture(mMusicLevelsTexture); mMusicLevelsTexture = nullptr;
	SDL_DestroyTexture(mSoundLevelsTexture); mSoundLevelsTexture = nullptr;
	SDL_DestroyTexture(mPipeTexture); mPipeTexture = nullptr;
	SDL_DestroyTexture(mPipeDownTexture); mPipeDownTexture = nullptr;
	SDL_DestroyTexture(mFloorTexture); mFloorTexture = nullptr;

	mFont = nullptr; TTF_CloseFont(mFont);
}

// Public Functions

void Renderer::RenderGameplay(int score)
{
	RenderBackground(GAMEPLAY);
	RenderPipes();

	if (mPlayer->IsDead()) RenderPlayer(mPlayerTexture[FALLING]);
	else {
		RenderScore(score);
		RenderPlayer(mPlayerTexture[FLYING]);
	}
	RenderFloor();

	if (Mix_PlayingMusic() == 0 || Mix_PausedMusic() == 1) {
		Mix_PlayMusic(mMusic[MUSICGAME], -1);
	}
}

void Renderer::RenderMenu(int state)
{

	RenderBackground(MENU);
	RenderFloor();

	if (state == 1) {
		RenderButton(BTNPLAY);
		RenderButton(BTNSCORE);
		RenderButton(BTNSETTINGS);
	}
}

void Renderer::RenderDeathScreen(int score, int highScore)
{
	mSrc.w = mBackground->GetScreenRect()->w;
	mSrc.h = mBackground->GetScreenRect()->h;
	SDL_RenderCopy(mRenderer, mScreenTexture[SCRDEATH], &mSrc, mBackground->GetScreenRect());

	RenderButton(BTNPLAY_AGAIN);
	RenderButton(BTNHOME);

	mText[TEXTSCOREDS] = std::to_string(score);
	mTextSurface[TEXTSCOREDS] = TTF_RenderText_Solid(mFont, mText[TEXTSCOREDS].c_str(), mColorBrown);
	mTextTexture[TEXTSCOREDS] = SDL_CreateTextureFromSurface(mRenderer, mTextSurface[TEXTSCOREDS]);
	SDL_RenderCopy(mRenderer, mTextTexture[TEXTSCOREDS], &mSrc, mBackground->GetTextRect(TEXTSCOREDS));

	mText[TEXTBEST] = std::to_string(highScore);
	mTextSurface[TEXTBEST] = TTF_RenderText_Solid(mFont, mText[TEXTBEST].c_str(), mColorBrown);
	mTextTexture[TEXTBEST] = SDL_CreateTextureFromSurface(mRenderer, mTextSurface[TEXTBEST]);
	SDL_RenderCopy(mRenderer, mTextTexture[TEXTBEST], &mSrc, mBackground->GetTextRect(TEXTBEST));

	ClearTextPointers(TEXTSCOREDS);
	ClearTextPointers(TEXTBEST);
}

void Renderer::RenderScoresScreen(int arr[5])
{
	mSrc.w = mBackground->GetScreenRect()->w;
	mSrc.h = mBackground->GetScreenRect()->h;
	SDL_RenderCopy(mRenderer, mScreenTexture[SCRSCORES], &mSrc, mBackground->GetScreenRect());

	mText[TEXT1] = std::to_string(arr[0]);
	mTextSurface[TEXT1] = TTF_RenderText_Solid(mFont, mText[TEXT1].c_str(), mColorBrown);
	mTextTexture[TEXT1] = SDL_CreateTextureFromSurface(mRenderer, mTextSurface[TEXT1]);
	SDL_RenderCopy(mRenderer, mTextTexture[TEXT1], &mSrc, mBackground->GetTextRect(TEXT1));

	mText[TEXT2] = std::to_string(arr[1]);
	mTextSurface[TEXT2] = TTF_RenderText_Solid(mFont, mText[TEXT2].c_str(), mColorBrown);
	mTextTexture[TEXT2] = SDL_CreateTextureFromSurface(mRenderer, mTextSurface[TEXT2]);
	SDL_RenderCopy(mRenderer, mTextTexture[TEXT2], &mSrc, mBackground->GetTextRect(TEXT2));

	mText[TEXT3] = std::to_string(arr[2]);
	mTextSurface[TEXT3] = TTF_RenderText_Solid(mFont, mText[TEXT3].c_str(), mColorBrown);
	mTextTexture[TEXT3] = SDL_CreateTextureFromSurface(mRenderer, mTextSurface[TEXT3]);
	SDL_RenderCopy(mRenderer, mTextTexture[TEXT3], &mSrc, mBackground->GetTextRect(TEXT3));

	mText[TEXT4] = std::to_string(arr[3]);
	mTextSurface[TEXT4] = TTF_RenderText_Solid(mFont, mText[TEXT4].c_str(), mColorBrown);
	mTextTexture[TEXT4] = SDL_CreateTextureFromSurface(mRenderer, mTextSurface[TEXT4]);
	SDL_RenderCopy(mRenderer, mTextTexture[TEXT4], &mSrc, mBackground->GetTextRect(TEXT4));

	mText[TEXT5] = std::to_string(arr[4]);
	mTextSurface[TEXT5] = TTF_RenderText_Solid(mFont, mText[TEXT5].c_str(), mColorBrown);
	mTextTexture[TEXT5] = SDL_CreateTextureFromSurface(mRenderer, mTextSurface[TEXT5]);
	SDL_RenderCopy(mRenderer, mTextTexture[TEXT5], &mSrc, mBackground->GetTextRect(TEXT5));

	for (int i = TEXT1; i < EMPTYTEXT; i++) {
		ClearTextPointers(i);
	}

	RenderButton(BTNRESETSCORE);
}

void Renderer::RenderSettingsScreen(int musicLevel, int soundLevel)
{
	mSrc.w = mBackground->GetScreenRect()->w;
	mSrc.h = mBackground->GetScreenRect()->h;
	SDL_RenderCopy(mRenderer, mScreenTexture[SCRSETTINGS], &mSrc, mBackground->GetScreenRect());

	// Depending on the level, render that many columns
	RenderAudioLevels(musicLevel, TYPEMUSIC);
	RenderAudioLevels(soundLevel, TYPESOUND);

	RenderButton(BTNLEFTVOLUME_ONE);
	RenderButton(BTNRIGHTVOLUME_ONE);
	RenderButton(BTNLEFTVOLUME_TWO);
	RenderButton(BTNRIGHTVOLUME_TWO);
}

void Renderer::PlaySound(int id)
{
	Mix_PlayChannel(-1, mSound[id], 0);
}

void Renderer::ChangeMusicLevel(int lvl)
{
	Mix_VolumeMusic(lvl);
}

void Renderer::ChangeSoundLevel(int lvl)
{
	Mix_Volume(-1, lvl);
}

// Private functions

void Renderer::RenderPlayer(SDL_Texture* texture)
{
	int animationLength = 6;
	int animationRate = 5;

	mPlayerAnimation[0].x = 0;
	mPlayerAnimation[0].y = 0;
	mPlayerAnimation[0].h = 50;
	mPlayerAnimation[0].w = 50;

	for (int i = 1; i < 6; i++) {
		mPlayerAnimation[i].x = 50 * i;
		mPlayerAnimation[i].y = 0;
		mPlayerAnimation[i].h = 50;
		mPlayerAnimation[i].w = 50;
	}

	int frameToDraw = ((SDL_GetTicks() - mStartTime) * animationRate / 1000) % animationLength;
	SDL_RenderCopy(mRenderer, texture, &mPlayerAnimation[frameToDraw], mPlayer->GetRect());
}

void Renderer::RenderAudioLevels(int musicLevel, int type)
{
	int frame = 0;
	SDL_Rect dest;

	switch (musicLevel)
	{
	case 21:
		frame = 0;
		break;
	case 18:
		frame = 250;
		break;
	case 15:
		frame = 500;
		break;
	case 12:
		frame = 750;
		break;
	case 9:
		frame = 1000;
		break;
	case 6:
		frame = 1250;
		break;
	case 3:
		frame = 1500;
		break;
	case 0:
		frame = 1750;
		break;
	default:
		break;
	}

	if (type == TYPEMUSIC) {
		dest = mAudio.GetMusicLevelRect();
	}
	else if (type == TYPESOUND) {
		dest = mAudio.GetSoundLevelRect();
	}

	mAudioLevelAnimation.x = frame;
	mAudioLevelAnimation.y = 0;
	mAudioLevelAnimation.w = 250;
	mAudioLevelAnimation.h = 50;

	SDL_RenderCopy(mRenderer, mMusicLevelsTexture, &mAudioLevelAnimation, &dest);
}

void Renderer::RenderPipes()
{
	mSrc.w = mPipes->GetPipeRect(0)->w;
	mSrc.h = mPipes->GetPipeRect(0)->h;

	for (int i = 0; i < mPipes->GetSize(); i++) {
		SDL_RenderCopy(mRenderer, mPipeTexture, &mSrc, mPipes->GetPipeRect(i));

		SDL_RenderCopy(mRenderer, mPipeDownTexture, &mSrc, mPipes->GetPipeDown(i));
	}
}

void Renderer::RenderFloor()
{
	mSrc.w = mBackground->GetFloorRect()->w;
	mSrc.h = mBackground->GetFloorRect()->h;

	SDL_RenderCopy(mRenderer, mFloorTexture, &mSrc, mBackground->GetFloorRect());
}

void Renderer::RenderBackground(BackgroundTextures texture)
{
	mSrc.w = mBackground->GetBackgroundRect()->w;
	mSrc.h = mBackground->GetBackgroundRect()->h;

	SDL_RenderCopy(mRenderer, mBackgroundTexture[texture], &mSrc, mBackground->GetBackgroundRect());
}

void Renderer::RenderButton(int btn)
{
	mSrc.w = mBackground->GetButtonRect(btn)->w;
	mSrc.h = mBackground->GetButtonRect(btn)->h;
	SDL_RenderCopy(mRenderer, mButtonTexture[btn], &mSrc, mBackground->GetButtonRect(btn));
}

void Renderer::RenderScore(int score)
{
	mText[TEXTSCOREGMP] = std::to_string(score);
	mTextSurface[TEXTSCOREGMP] = TTF_RenderText_Solid(mFont, mText[TEXTSCOREGMP].c_str(), mColorBrown);
	mTextTexture[TEXTSCOREGMP] = SDL_CreateTextureFromSurface(mRenderer, mTextSurface[TEXTSCOREGMP]);
	SDL_RenderCopy(mRenderer, mTextTexture[TEXTSCOREGMP], &mSrc, mBackground->GetTextRect(TEXTSCOREGMP));
	ClearTextPointers(TEXTSCOREGMP);
}

void Renderer::InitTextures()
{
	mPlayerTexture[FLYING] = IMG_LoadTexture(mRenderer, mPlayer->GetFlyingTexture().c_str());
	mPlayerTexture[FALLING] = IMG_LoadTexture(mRenderer, mPlayer->GetFallingTexture().c_str());
	mMusicLevelsTexture = IMG_LoadTexture(mRenderer, mAudio.GetAudioLevelsTexture().c_str());
	mSoundLevelsTexture = IMG_LoadTexture(mRenderer, mAudio.GetAudioLevelsTexture().c_str());
	mPipeTexture = IMG_LoadTexture(mRenderer, mPipes->GetPipe().c_str());
	mPipeDownTexture = IMG_LoadTexture(mRenderer, mPipes->GetPipeDown().c_str());
	mFloorTexture = IMG_LoadTexture(mRenderer, mBackground->GetFloorTexture().c_str());

	mBackgroundTexture[GAMEPLAY] = IMG_LoadTexture(mRenderer, mBackground->GetBackgroundTexture(GAMEPLAY).c_str());
	mBackgroundTexture[MENU] = IMG_LoadTexture(mRenderer, mBackground->GetBackgroundTexture(MENU).c_str());
	mScreenTexture[SCRDEATH] = IMG_LoadTexture(mRenderer, mBackground->GetScreenBackground(SCRDEATH).c_str());
	mScreenTexture[SCRSCORES] = IMG_LoadTexture(mRenderer, mBackground->GetScreenBackground(SCRSCORES).c_str());
	mScreenTexture[SCRSETTINGS] = IMG_LoadTexture(mRenderer, mBackground->GetScreenBackground(SCRSETTINGS).c_str());

	mButtonTexture[BTNPLAY] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNPLAY).c_str());
	mButtonTexture[BTNSCORE] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNSCORE).c_str());
	mButtonTexture[BTNPLAY_AGAIN] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNPLAY_AGAIN).c_str());
	mButtonTexture[BTNHOME] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNHOME).c_str());
	mButtonTexture[BTNRESETSCORE] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNRESETSCORE).c_str());
	mButtonTexture[BTNSETTINGS] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNSETTINGS).c_str());
	mButtonTexture[BTNRIGHTVOLUME_ONE] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNRIGHTVOLUME_ONE).c_str());
	mButtonTexture[BTNLEFTVOLUME_ONE] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNLEFTVOLUME_ONE).c_str());
	mButtonTexture[BTNRIGHTVOLUME_TWO] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNRIGHTVOLUME_TWO).c_str());
	mButtonTexture[BTNLEFTVOLUME_TWO] = IMG_LoadTexture(mRenderer, mBackground->GetButtonTexture(BTNLEFTVOLUME_TWO).c_str());
}

void Renderer::InitAudio()
{
	mSound[SOUNDBUTTON] = Mix_LoadWAV(mAudio.GetSound(SOUNDBUTTON).c_str());
	mSound[SOUNDDIE] = Mix_LoadWAV(mAudio.GetSound(SOUNDDIE).c_str());
	mMusic[MUSICGAME] = Mix_LoadMUS(mAudio.GetMusic(MUSICGAME).c_str());
}

void Renderer::ClearTextPointers(int id)
{
	SDL_DestroyTexture(mTextTexture[id]); mTextTexture[id] = nullptr;
	SDL_FreeSurface(mTextSurface[id]); mTextSurface[id] = nullptr;
}
