#include "Collision.h"

bool Collision::CheckPipeCollision(const SDL_Rect* playerRect, const SDL_Rect* pipeRect, const SDL_Rect* pipeDownRect)
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

bool Collision::CheckForScoreUpdate(const SDL_Rect* playerRect, const SDL_Rect* pipeRect)
{
	if (playerRect->x + playerRect->w == pipeRect->x + (pipeRect->w / 2)) return true;
	return false;
}

bool Collision::CheckFloorCollision(const SDL_Rect* playerRect, const int height)
{
	if (playerRect->y + playerRect->h >= height - 80) {
		return true;
	}
	return false;
}

bool Collision::CheckCeilingCollision(const SDL_Rect* playerRect)
{
	if (playerRect->y <= 0) {
		return true;
	}
	return false;
}
