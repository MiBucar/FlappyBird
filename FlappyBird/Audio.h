#pragma once
#include <iostream>
#include <string>
#include <Objects.h>
#include <SDL.h>
using namespace obj;

class Audio
{
public:
	Audio(int width, int height);

	// Getters
	std::string GetSound(int id) const { return mSound[id]; };
	std::string GetMusic(int id) const { return mMusic[id]; };
	std::string GetAudioLevelsTexture() const { return mLevelsTexture; };
	SDL_Rect GetMusicLevelRect() const { return mMusicLevelRect; };
	SDL_Rect GetSoundLevelRect() const { return mSoundLevelRect; };
private:
	std::string mSound[EMPTYSOUND];
	std::string mMusic[EMPTYMUSIC];
	std::string mLevelsTexture;

	SDL_Rect mMusicLevelRect;
	SDL_Rect mSoundLevelRect;
};

