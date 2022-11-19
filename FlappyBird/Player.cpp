#include "Player.h"

Player::Player(const int width, const int height) : mTexture("images//FlappyBirdAnimation.png"),
mRect{width / 2 - 50,  height / 2 - 50, 50, 50}, mFallSpeed(1.5)
{
	mJumpHeight = 20;
}

Player::~Player()
{
}

void Player::Move()
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	if (state[SDL_SCANCODE_SPACE]) {
		mRect.y = mRect.y - .5;
	}
	else {
		mRect.y += mFallSpeed;
	}
}

