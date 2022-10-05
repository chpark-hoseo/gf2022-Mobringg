#include "Game.h"
#include <SDL2/SDL_image.h>
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
    }

    ;
    SDL_Surface* pTempSurface = IMG_Load("assets/bus.png");
    //SDL_Surface* pTempBackground = SDL_LoadBMP("assets/animate.bmp");
    

    
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    //m_pTexture1 = SDL_CreateTextureFromSurface(m_pRenderer, pTempBackground);
   
  
    SDL_FreeSurface(pTempSurface);
    //SDL_FreeSurface(pTempBackground);
    

  

    m_sourceRectangle.w = 500;
    m_sourceRectangle.h = 500;

    m_sourceRectangle1.w = 128;
    m_sourceRectangle1.h = 82;

    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    m_destinationRectangle1.w = m_sourceRectangle1.w;
    m_destinationRectangle1.h = m_sourceRectangle1.h;

    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;

    m_destinationRectangle1.x = 0;
    m_destinationRectangle1.y = 80;


   

    m_bRunning = true;
    return true;
}

void Game::update()
{
    /*if (m_destinationRectangle.x <= 0)
    {
        dir = 1;
    }
    else if (m_destinationRectangle.x >= 480-m_destinationRectangle.w)
    {
        dir = -1;
    }
    m_destinationRectangle.x += dir;
    SDL_Delay(10);*/

    m_sourceRectangle.x = 128 * ((SDL_GetTicks() / 100) % 6);
    m_sourceRectangle1.x = 128 * ((SDL_GetTicks() / 50) % 6);
}



void Game::render()
{
    
    SDL_RenderClear(m_pRenderer);
    
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderCopy(m_pRenderer, m_pTexture1, &m_sourceRectangle1, &m_destinationRectangle1);

  
    SDL_RenderPresent(m_pRenderer);
    
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
    SDL_DestroyTexture(m_pTexture);
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}