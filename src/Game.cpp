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
    }

   // SDL_Surface* pTempBackground = SDL_LoadBMP("assets/123.bmp");
    SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
    

    //m_pTexture1 = SDL_CreateTextureFromSurface(m_pRenderer, pTempBackground);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
   
    //SDL_FreeSurface(pTempBackground);
    SDL_FreeSurface(pTempSurface);
    
   /* SDL_QueryTexture(m_pTexture1, NULL, NULL,
        &m_sourceRectangle1.w, &m_sourceRectangle1.h);*/

    SDL_QueryTexture(m_pTexture, NULL, NULL,
    &m_sourceRectangle.w, &m_sourceRectangle.h);

    //실습
    //m_destinationRectangle.w = m_sourceRectangle.w = 50;
    //m_destinationRectangle.h = m_sourceRectangle.h = 50;

    //m_destinationRectangle.x = m_sourceRectangle.x = 0;
    //m_destinationRectangle.y = m_sourceRectangle.y = 0;
  
    //과제 1번
   // m_destinationRectangle.w = m_sourceRectangle.w = 30;
   // m_destinationRectangle.h = m_sourceRectangle.h = 30;

    //과제 2번
    //m_destinationRectangle.w = m_sourceRectangle.w = 40;
    //m_destinationRectangle.h = m_sourceRectangle.h = 40;

    //과제 3번
    //m_destinationRectangle.w = m_sourceRectangle.w = 480;
    //m_destinationRectangle.h = m_sourceRectangle.h = 640;
   
    //과제 1번
   // m_destinationRectangle.x = m_sourceRectangle.x = 10;
   // m_destinationRectangle.y = m_sourceRectangle.y = 10;

    //과제 2번
    //m_destinationRectangle.x = m_sourceRectangle.x = 50;
    //m_destinationRectangle.y = m_sourceRectangle.y = 50;

    //과제 3번
    //m_destinationRectangle.x = m_sourceRectangle.x = 0;
    //m_destinationRectangle.y = m_sourceRectangle.y = 0;

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
}



void Game::render()
{
    
    SDL_RenderClear(m_pRenderer);
    SDL_RenderCopy(m_pRenderer, m_pTexture1, &m_sourceRectangle1, &m_destinationRectangle1);
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);

  
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