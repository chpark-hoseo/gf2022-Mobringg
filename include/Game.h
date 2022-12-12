#pragma once

#include <SDL2/SDL.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Vector2D.h"
#include <vector>
#define TILE_SIZE 75
#define collisionCount 100

class GameObject;

struct Wall
{
	int u, d, l, r;
};

class Game
{
public:
	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
	void render();
	void update();
	bool running();
	void handleEvents();
	void clean();
	void quit() { m_bRunning = false; }
	
	int alphaS = 1;
	int alpha_x;
	int alpha_y;

private:
	std::vector<GameObject*> m_gameObjects;
	Game() { }
	static Game* s_pInstance;

	

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;
	int m_currentFrame;

	Wall wall[100];
	Wall wallDes;

	

	
	
	
	
	


};

typedef Game TheGame;