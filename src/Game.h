#pragma once

#include <SDL2/SDL.h>
#include "TextureManager.h"
#define TILE_SIZE 75
#define collisionCount 100

//������ �浹 �̱��� - ���� ������Ʈ


//������ ������ - ���� ���� ���
/*const int LEVEL_WIDTH = 640;
const int LEVEL_HEIGHT = 480;*/

//�ʿ� �򸮴� Ÿ���� ���� - �̹����� ��ü�Ϸ�
/*const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;*/

struct Wall
{
	int u, d, l, r;
};

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
	void chr();
	
	int alphaS = 1;
	int alpha_x;
	int alpha_y;
	
	
private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
	int m_currentFrame;

	Wall wall[100];
	Wall wallDes;

	typedef struct SDL_Rect
	{
		int x, y;
		int w, h;
	} SDL_Rect;
};


