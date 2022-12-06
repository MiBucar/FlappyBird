#include "Background.h"

Background::Background(int width, int height) : mFloor("images//Floor.png"), mFloorRect{ 0, height - 80, 2000, 80 }, mBackgroundRect{0, 0, 1280, 640}, mWidth(width), mHeight(height),
mDeathScreenRect{width/2 - 250, height/2 - 250, 500, 400}
{
	mBackground[BackgroundTextures::GAMEPLAY] = "images//Background.png";
	mBackground[BackgroundTextures::MENU] = "images//MenuBackground.png";
	mButton[Buttons::PLAY] = "images//PlayButton.png";
	mButton[Buttons::PLAY_AGAIN] = "images//PlayAgainButton.png";
	mButton[Buttons::HOME] = "images//HomeButton.png";
	mDeathScreen = "images//DeathScreen.png";

	for (int i = 0; i < sizeof(mButtonRect) / sizeof(mButtonRect[0]); i++) {
		mButtonRect[i].w = 160;
		mButtonRect[i].h = 70;
	}

	const int centerRight = mWidth / 2 - 200;
	const int centerLeft = mWidth / 2 + (200 - 160);
	const int center = mWidth / 2 - 80;

	mButtonRect[Buttons::PLAY].x = centerRight; mButtonRect[Buttons::PLAY].y = 400;
	mButtonRect[Buttons::PLAY_AGAIN].x = centerRight; mButtonRect[Buttons::PLAY_AGAIN].y = 540;
	mButtonRect[Buttons::HOME].x = centerLeft; mButtonRect[Buttons::HOME].y = 540;
}

void Background::MoveFloor(float speed)
{
	mFloorRect.x -= speed;
	if (mFloorRect.x == -720) {
		mFloorRect.x = 0;
	}
}
