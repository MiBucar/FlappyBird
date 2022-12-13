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
	const SDL_Rect* GetAudioLevelRect() const { return &mAudioLevelRect; };
private:
	std::string mSound[EMPTYSOUND];
	std::string mMusic[EMPTYMUSIC];
	std::string mLevelsTexture;

	SDL_Rect mAudioLevelRect;
};

