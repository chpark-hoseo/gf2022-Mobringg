#pragma once

#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"




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

	

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
	int m_currentFrame;

	GameObject m_go;
	Player m_player;

	typedef struct SDL_Rect
	{
		int x, y;
		int w, h;
	} SDL_Rect;
};
