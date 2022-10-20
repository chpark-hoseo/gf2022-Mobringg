#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        m_pWindow = SDL_CreateWindow(
            title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(
                    m_pRenderer, 255, 255, 255, 255);
            }
            else {
                return false; // 랜더러 생성 실패
            }
        }
        else {
            return false; // 윈도우 생성 실패
        }
    }
    else {
        return false; // SDL 초기화 실패
    };

 
    if (!TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
    {
        return false;
    }

    m_bRunning = true;
    return true;
}

void Game::update()
{
    m_currentFrame = ((SDL_GetTicks() / 100) % 6);
}



void Game::render()
{
    
    SDL_RenderClear(m_pRenderer);
    
    TheTextureManager::Instance()->draw("animate", 0, 0, 128, 82, m_pRenderer);
    TheTextureManager::Instance()->drawFrame("animate", 100, 100, 128, 82, 0, m_currentFrame, m_pRenderer);

  
    SDL_RenderPresent(m_pRenderer);
    
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            m_bRunning = false;
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                x--;
            }
        }
    }
}

void Game::clean() 
{
    
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}