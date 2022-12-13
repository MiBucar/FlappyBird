#include "Audio.h"

Audio::Audio(int width, int height)
{
	mSound[SOUNDBUTTON] = "sound//Button.wav";
	mSound[SOUNDDIE] = "sound//Die.wav";
	mMusic[MUSICGAME] = "sound/Jazz.mp3";
	mLevelsTexture = "images//AudioLevels.png";

	mMusicLevelRect.w = 250;
	mMusicLevelRect.h = 50;
	mMusicLevelRect.x = width / 2 - (mMusicLevelRect.w / 2);
	mMusicLevelRect.y = 310;

	mSoundLevelRect.w = 250;
	mSoundLevelRect.h = 50;
	mSoundLevelRect.x = width / 2 - (mSoundLevelRect.w / 2);
	mSoundLevelRect.y = 420;
}
