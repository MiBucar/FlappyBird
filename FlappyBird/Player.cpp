#include "Player.h"

Player::Player(const int width, const int height) : mFlyingTexture("images//FlappyBirdAnimation.png"), mFallingTexture("images//FlappyBirdFallingAnimation.png"),
mRect{width / 2 - 50,  height / 2 - 50, 50, 50}, mFallSpeed(1.5)
{
	mJumpHeight = 20;
}

Player::~Player()
{
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

