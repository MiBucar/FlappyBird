#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

int main(int argc, char* args[]) {
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	const int width = 1280;
	const int height = 720;
	bool isRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Failed to init the video: " << SDL_GetError() << "\n";
	}
	else {
		mWindow = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
		mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
	}

	SDL_Event event;
	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			}
		}
	}

	return 0;
}