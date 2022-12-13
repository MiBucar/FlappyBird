#include "Audio.h"

Audio::Audio(int width, int height)
{
	mSound[SOUNDBUTTON] = "sound//Button.wav";
	mMusic[MUSICGAME] = "sound/Jazz2.mp3";
	mLevelsTexture = "images//AudioLevels.png";

	mAudioLevelRect.w = 250;
	mAudioLevelRect.h = 50;
	mAudioLevelRect.x = width / 2 - (mAudioLevelRect.w / 2);
	mAudioLevelRect.y = 310;
}
