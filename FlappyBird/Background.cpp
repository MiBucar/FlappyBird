#include "Background.h"

Background::Background(int width, int height) : mFloor("images//Floor.png"), mFloorRect{ 0, height - 80, 2000, 80 }, mBackgroundRect{0, 0, 1280, 640}, mWidth(width), mHeight(height),
mScreenRect{width/2 - 250, height/2 - 250, 500, 400}
{
	mBackgroundTexture[GAMEPLAY] = "images//Background.png";
	mBackgroundTexture[MENU] = "images//MenuBackground.png";
	mScreenTexture[SCRDEATH] = "images//DeathScreen.png";
	mScreenTexture[SCRSCORES] = "images//ScoresScreen.png";
	mScreenTexture[SCRSETTINGS] = "images//SettingsScreen.png";

	InitButton();
	InitText();
}

void Background::MoveFloor(int speed)
{
	mFloorRect.x -= speed;
	if (mFloorRect.x == -720) {
		mFloorRect.x = 0;
	}
}

void Background::InitButton()
{
	mButtonTexture[BTNPLAY] = "images//PlayButton.png";
	mButtonTexture[BTNPLAY_AGAIN] = "images//PlayAgainButton.png";
	mButtonTexture[BTNHOME] = "images//HomeButton.png";
	mButtonTexture[BTNSCORE] = "images//ScoresButton.png";
	mButtonTexture[BTNRESETSCORE] = "images//PlayAgainButton.png";
	mButtonTexture[BTNSETTINGS] = "images//SettingsButton.png";
	mButtonTexture[BTNRIGHTVOLUME_ONE] = "images//RightVolumeButton.png";
	mButtonTexture[BTNLEFTVOLUME_ONE] = "images//LeftVolumeButton.png";
	mButtonTexture[BTNRIGHTVOLUME_TWO] = "images//RightVolumeButton.png";
	mButtonTexture[BTNLEFTVOLUME_TWO] = "images//LeftVolumeButton.png";

	for (int i = 0; i < sizeof(mButtonRect) / sizeof(mButtonRect[0]); i++) {
		mButtonRect[i].w = 160;
		mButtonRect[i].h = 70;
	}

	const int centerRight = mWidth / 2 - 200;
	const int centerLeft = mWidth / 2 + (200 - 160);
	const int center = mWidth / 2 - 80;

	mButtonRect[BTNPLAY].x = centerRight; mButtonRect[BTNPLAY].y = 400;
	mButtonRect[BTNSCORE].x = centerLeft; mButtonRect[BTNSCORE].y = 400;
	mButtonRect[BTNPLAY_AGAIN].x = centerRight; mButtonRect[BTNPLAY_AGAIN].y = 540;
	mButtonRect[BTNHOME].x = centerLeft; mButtonRect[BTNHOME].y = 540;
	mButtonRect[BTNRESETSCORE].x = center; mButtonRect[BTNRESETSCORE].y = mHeight / 2 + 175;
	mButtonRect[BTNSETTINGS].x = center; mButtonRect[BTNSETTINGS].y = mHeight / 2 + 150;

	mButtonRect[BTNLEFTVOLUME_ONE] = {
		mWidth / 2 - 190, 310, 60, 50
	};

	mButtonRect[BTNRIGHTVOLUME_ONE] = {
		mWidth / 2 + 130, 310, 60, 50
	};

	mButtonRect[BTNLEFTVOLUME_TWO] = {
		mWidth / 2 - 190, 420, 60, 50
	};

	mButtonRect[BTNRIGHTVOLUME_TWO] = {
		mWidth / 2 + 130, 420, 60, 50
	};
}

void Background::InitText()
{

	mTextRect[TEXTSCOREGMP] = { mWidth / 2 - 15, 50, 30, 70 };
	mTextRect[TEXTSCOREDS] = { mWidth / 2 + 200 - 20, 330, 20, 50 };
	mTextRect[TEXTBEST] = { mWidth / 2 + 200 - 20, 430, 20, 50 };
	mTextRect[TEXT1] = { mWidth / 2 - 70, mHeight / 2 - 173 + 40, 20, 40 };
	mTextRect[TEXT2] = { mWidth / 2 - 70, mHeight / 2 - 123 + 40, 20, 40 };
	mTextRect[TEXT3] = { mWidth / 2 - 70, mHeight / 2 - 73 + 40, 20, 40 };
	mTextRect[TEXT4] = { mWidth / 2 - 70, mHeight / 2 - 23 + 40, 20, 40 };
	mTextRect[TEXT5] = { mWidth / 2 - 70, mHeight / 2 + 23 + 40, 20, 40 };
}
