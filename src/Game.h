#include <SDL2/SDL.h>

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
	SDL_Texture* m_pTexture;
	SDL_Texture* m_pTexture1;

	// 원본 사각형
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_sourceRectangle1;

	// 대상 사각형
	SDL_Rect m_destinationRectangle;
	SDL_Rect m_destinationRectangle1;

	typedef struct SDL_Rect
	{
		int x, y;
		int w, h;
	} SDL_Rect;
};
