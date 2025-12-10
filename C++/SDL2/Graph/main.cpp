#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int NUM_RECTS = SCREEN_WIDTH;
const int RECT_WIDTH = SCREEN_WIDTH / NUM_RECTS;

int main() {
	srand(time(NULL));

	int* values = new int[NUM_RECTS];

	for (int i = 0; i < NUM_RECTS; i++) {
		values[i] = rand() % (NUM_RECTS + 1);
	}

	SDL_Rect* rectangles = new SDL_Rect[NUM_RECTS];

	for (int i = 0; i < NUM_RECTS; i++) {
		int value = values[i];
		rectangles[i].x = RECT_WIDTH * i;
		rectangles[i].y = SCREEN_HEIGHT - value;
		rectangles[i].w = RECT_WIDTH;
		rectangles[i].h = value;
	}

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error initializing" << std::endl;
	}
	else {
		window = SDL_CreateWindow("Selection Sort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		if (window == nullptr) {
			std::cout << "Window fail" << std::endl;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);

			SDL_Event e;
			bool quit = false;

			for (int i = 0; i < NUM_RECTS; i++) {
				int minInd = i;

				for (int j = i; j < NUM_RECTS; j++) {
					if (values[j] < values[minInd]) {
						minInd = j;
					}
				}

				if (minInd != i) {
					int temp = values[i];
					values[i] = values[minInd];
					values[minInd] = temp;
				}

				for (int j = 0; j < NUM_RECTS; j++) {
					SDL_FillRect(screenSurface, &rectangles[j], SDL_MapRGB(screenSurface->format, 0, 0, 0));
				}

				for (int j = 0; j < NUM_RECTS; j++) {
					int value = values[j];
					rectangles[j].y = SCREEN_HEIGHT - value;
					rectangles[j].h = value;
				}

				for (int j = 0; j < NUM_RECTS; j++) {
					SDL_FillRect(screenSurface, &rectangles[j], SDL_MapRGB(screenSurface->format, 255, 255, 255));
				}

				SDL_UpdateWindowSurface(window);

				Uint32 timeout = SDL_GetTicks() + 17;

				while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout));	
			}

			while (!quit) {
				while(SDL_PollEvent(&e)) {
					if(e.type == SDL_QUIT) {
						quit = true;
					}
				}
			}
		}
	}

	SDL_DestroyWindow(window);

	delete[] rectangles;
	delete[] values;

	SDL_Quit();	

	return 0;
}