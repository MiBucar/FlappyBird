#include "Collision.h"

bool Collision::CheckCollision(const SDL_Rect* playerRect, const SDL_Rect* pipeRect, const SDL_Rect* pipeDownRect)
{
	if (playerRect->y <= pipeDownRect->y + pipeDownRect->h &&
		playerRect->x + playerRect->w <= pipeDownRect->x + pipeDownRect->w &&
		playerRect->x + playerRect->w >= pipeDownRect->x) {
		return true;
	}

	if (playerRect->y + playerRect->h >= pipeRect->y &&
		playerRect->x + playerRect->w <= pipeDownRect->x + pipeDownRect->w &&
		playerRect->x + playerRect->w >= pipeDownRect->x) {
		return true;
	}

	return false;
}
