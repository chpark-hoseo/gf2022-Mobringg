#pragma once

#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"



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
	Monster m_monster;
	Monster m_monster2;

	typedef struct SDL_Rect
	{
		int x, y;
		int w, h;
	} SDL_Rect;
};
