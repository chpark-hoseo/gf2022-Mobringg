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

 
    if (!TheTextureManager::Instance()->load("assets/145.bmp", "Chr", m_pRenderer))
    {
        return false;
    }

    m_bRunning = true;
    return true;
}
void Game::update()
{
    man();
    m_currentFrame = ((SDL_GetTicks() / 100) % 5);
    SDL_Delay(5);
    
}

void Game::man()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        alphaS = 2;
        alpha_x -= 1;
        m_currentFrame = ((SDL_GetTicks() / 100) % 4);

    }

    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        alphaS = 1;
        alpha_x += 1;
        m_currentFrame = ((SDL_GetTicks() / 100) % 4);

    }

    else if (currentKeyStates[SDL_SCANCODE_UP])
    {
        alphaS = 3;
        alpha_y -= 1;
        m_currentFrame = ((SDL_GetTicks() / 100) % 4);
    }

    else if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        alphaS = 4;
        alpha_y += 1;
        m_currentFrame = ((SDL_GetTicks() / 100) % 4);
    }
}



void Game::render()
{
    
    SDL_RenderClear(m_pRenderer);
    
    if (alphaS == 1)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 0, m_currentFrame, m_pRenderer);
    else if (alphaS == 2)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 1, m_currentFrame, m_pRenderer);
    else if (alphaS == 3)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 2, m_currentFrame, m_pRenderer);
    else if (alphaS == 4)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 3, m_currentFrame, m_pRenderer);

  
    SDL_RenderPresent(m_pRenderer);
    TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 0, m_currentFrame, m_pRenderer);
}

bool Game::running()
{
    return m_bRunning;
}

void Game::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_bRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::clean() 
{
    
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}