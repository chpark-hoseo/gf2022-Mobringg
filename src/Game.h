#pragma once

#include <SDL2/SDL.h>
#include "TextureManager.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 640;
const int LEVEL_HEIGHT = 480;

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

const int TILE_RED = 0;
const int TILE_GREEN = 1;

class Game
{
public:
	Game() { }
	~Game() { }

	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();
	void man();
	
	int alphaS = 1;
	int alpha_x;
	int alpha_y;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
	int m_currentFrame;

	

	typedef struct SDL_Rect
	{
		int x, y;
		int w, h;
	} SDL_Rect;
};
