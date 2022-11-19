#include "Background.h"

Background::Background(int height) : mFloor("images//Floor.png"), mFloorRect{ 0, height - 80, 2000, 80 },
mBackground("images//Background.png"), mBackgroundRect{ 0, 0, 1280, 640 }
{
}

void Background::MoveFloor()
{
	mFloorRect.x -= 1;
	if (mFloorRect.x == -720) {
		mFloorRect.x = 0;
	}
}
