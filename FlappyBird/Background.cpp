#include "Background.h"

Background::Background(int width, int height) : mFloor("images//Floor.png"), mFloorRect{ 0, height - 80, 2000, 80 }, mBackgroundRect{0, 0, 1280, 640}, mWidth(width), mHeight(height),
mDeathScreenRect{width/2 - 250, height/2 - 250, 500, 400}
{
	mBackground[BackgroundTextures::GAMEPLAY] = "images//Background.png";
	mBackground[BackgroundTextures::MENU] = "images//MenuBackground.png";
	mButton[Buttons::BTNPLAY] = "images//PlayButton.png";
	mButton[Buttons::BTNPLAY_AGAIN] = "images//PlayAgainButton.png";
	mButton[Buttons::BTNHOME] = "images//HomeButton.png";
	mDeathScreen = "images//DeathScreen.png";

	for (int i = 0; i < sizeof(mButtonRect) / sizeof(mButtonRect[0]); i++) {
		mButtonRect[i].w = 160;
		mButtonRect[i].h = 70;
	}

	const int centerRight = mWidth / 2 - 200;
	const int centerLeft = mWidth / 2 + (200 - 160);
	const int center = mWidth / 2 - 80;

	mButtonRect[Buttons::BTNPLAY].x = centerRight; mButtonRect[Buttons::BTNPLAY].y = 400;
	mButtonRect[Buttons::BTNPLAY_AGAIN].x = centerRight; mButtonRect[Buttons::BTNPLAY_AGAIN].y = 540;
	mButtonRect[Buttons::BTNHOME].x = centerLeft; mButtonRect[Buttons::BTNHOME].y = 540;

	mTextRect[TEXTSCOREGMP] = { mWidth / 2 - 15, 50, 30, 100 };
	mTextRect[TEXTSCOREDS] = { mWidth / 2 + 200 - 15, 330, 15, 50};
	mTextRect[TEXTBEST] = { mWidth / 2 + 200 - 15, 430, 15, 50 };
}

void Background::MoveFloor(int speed)
{
	mFloorRect.x -= speed;
	if (mFloorRect.x == -720) {
		mFloorRect.x = 0;
	}
}
