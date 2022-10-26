#pragma once

#include <SDL2/SDL.h>
#include "TextureManager.h"
#define TILE_SIZE 75
#define collisionCount 100

//벽과의 충돌 미구현 - 최종 업데이트


//레벨층 사이즈 - 레벨 구현 취소
/*const int LEVEL_WIDTH = 640;
const int LEVEL_HEIGHT = 480;*/

//맵에 깔리는 타일의 정보 - 이미지로 대체완료
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


