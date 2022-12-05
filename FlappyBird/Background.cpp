#include "Background.h"

Background::Background(int width, int height) : mFloor("images//Floor.png"), mFloorRect{ 0, height - 80, 2000, 80 }, mBackgroundRect{0, 0, 1280, 640}, mWidth(width), mHeight(height),
mDeathScreenRect{width/2 - 250, height/2 - 250, 500, 400}
{
	mBackground[GAMEPLAY] = "images//Background.png";
	mBackground[MENU] = "images//MenuBackground.png";
	mButton[PLAY] = "images//PlayButton.png";
	mButton[PLAY_AGAIN] = "images//PlayAgainButton.png";
	mDeathScreen = "images//DeathScreen.png";

	mButtonRect[PLAY] = { mWidth / 2 - 200, 400, 160, 70 };
	mButtonRect[PLAY_AGAIN] = { mWidth / 2 - 200, 550, 160, 70 };
}

void Background::MoveFloor(float speed)
{
	mFloorRect.x -= speed;
	if (mFloorRect.x == -720) {
		mFloorRect.x = 0;
	}
}
