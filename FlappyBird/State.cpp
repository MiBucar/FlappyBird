#include "State.h"

State::State()
{
}

void State::Playing()
{
	mRenderer.RenderGame();

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_F]) {
		mRenderer.SetActive();
	}
}
