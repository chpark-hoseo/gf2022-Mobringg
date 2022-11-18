#include "Game.h"
#include "TextureManager.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
    Uint32 frameStart, frameTime;
    if (TheGame::Instance()->init("Chapter 1",
        100, 100, 640, 480, false))
    {
        while (TheGame::Instance()->running()) {
            frameStart = SDL_GetTicks();     // step 1
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();
            frameTime = SDL_GetTicks() - frameStart;  // step 2
            if (frameTime < DELAY_TIME) {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
    }
    TheGame::Instance()->clean();
    return 0;
}