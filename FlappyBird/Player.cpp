#include "Player.h"

Player::Player(const int width, const int height) : mWidth(width), mHeight(height), mFlyingTexture("images//FlappyBirdAnimation.png"), mFallingTexture("images//FlappyBirdFallingAnimation.png"),
mRect{mWidth / 2 - 50,  mHeight / 2 - 50, 50, 50}, mFallSpeed(1.5)
{
	mJumpHeight = 20;
}

void Player::Move(bool gameStarted)
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	if (gameStarted) {
		if (mIsDead == false) {
			if (state[SDL_SCANCODE_SPACE]) {
				mRect.y = mRect.y - .5;
			}
			else {
				mRect.y += mFallSpeed;
			}
		}
		else {
			mRect.y += 2;
			if (mRect.y >= 600) {  // if the player died, make him fall onto the floor
				mRect.y = 600;
			}
		}
	}
}

void Player::Start()
{
	mRect.x = mWidth / 2 - 50;
	mRect.y = mHeight / 2 - 50;
	mRect.h = 50;
	mRect.w = 50;
}

void Player::Block()
{
	mRect.y = 0;
}

