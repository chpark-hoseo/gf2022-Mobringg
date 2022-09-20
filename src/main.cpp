#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <iostream>
using namespace std;



#include "main.h"


	


SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;
bool g_bRunning = false;
bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
void Render();

int main(int argc, char* argv[])
{
	if (init("Breaking Up HelloSDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480,
		SDL_WINDOW_SHOWN))
	{
		g_bRunning = true;
	}
	else
	{
		return 1;
	}
	while (g_bRunning < 10)
	{
		g_bRunning++;
		SDL_SetRenderDrawColor(g_pRenderer, rand() % 256, rand() % 256, rand() % 256, 255);
		SDL_Delay(1000);
		Render();

		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				printf("Key press detected\n");
				SDL_Quit();
				break;
			case SDL_KEYUP:
				printf("Key release detected\n");
				break;
			}
		}
	}

	SDL_Quit();
	return 0;
}

bool init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		g_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		if (g_pWindow != 0) {
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}
	}
	else {
		return false;
	}

	return true;
}

void Render()
{
	SDL_RenderClear(g_pRenderer);

	SDL_RenderPresent(g_pRenderer);
}

