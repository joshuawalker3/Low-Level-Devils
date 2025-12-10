#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int RECT_WIDTH = 1;
const int RECT_HEIGHT = 1;

int main() {
	srand(time(NULL));

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;

	SDL_Rect** rectangles = new SDL_Rect*[SCREEN_HEIGHT / RECT_HEIGHT];

	for (int i = 0; i < SCREEN_HEIGHT / RECT_HEIGHT; i++) {
		rectangles[i] = new SDL_Rect[SCREEN_WIDTH / RECT_WIDTH];
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error initializing" << std::endl;
	}
	else {
		window = SDL_CreateWindow("Static", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

		if (window == nullptr) {
			std::cout << "Window fail" << std::endl;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);

			SDL_Event e;
			bool quit = false;

			while (!quit) {
				for (int i = 0; i < SCREEN_HEIGHT / RECT_HEIGHT; i++) {
					int rect_x = 0;
					int rect_y = i * RECT_HEIGHT;
					for (int j = 0; j < SCREEN_WIDTH / RECT_WIDTH; j++) {
						rect_x = j * RECT_WIDTH;
						rectangles[i][j].x = rect_x;
						rectangles[i][j].y = rect_y;
						rectangles[i][j].w = RECT_WIDTH;
						rectangles[i][j].h = RECT_HEIGHT;
					}
				}

				for (int i = 0; i < SCREEN_HEIGHT / RECT_HEIGHT; i++) {
					for (int j = 0; j < SCREEN_WIDTH / RECT_WIDTH; j++) {
						int red = rand() % 256;
						int green = rand() % 256;
						int blue = rand() % 256;

						SDL_FillRect(screenSurface, &rectangles[i][j], SDL_MapRGB(screenSurface->format, red, green, blue));
					}
				}

				SDL_UpdateWindowSurface(window);

				while(SDL_PollEvent(&e)) {
					if(e.type == SDL_QUIT) {
						quit = true;
					}
				}
			}
		}
	}

	SDL_DestroyWindow(window);

	for (int i = SCREEN_WIDTH / RECT_WIDTH; i > 0;) {
		delete[] rectangles[--i];
	}

	delete[] rectangles;

	SDL_Quit();	

	return 0;
}