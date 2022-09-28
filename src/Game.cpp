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
            return false; // 윈도우 생설 실패 l
        }
    }
    else {
        return false; // SDL 초기화 실패
    }


    SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
    SDL_Surface* pTempBackground = SDL_LoadBMP("assets/123.bmp");

    m_pTexture1 = SDL_CreateTextureFromSurface(m_pRenderer, pTempBackground);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
   
    SDL_FreeSurface(pTempBackground);
    SDL_FreeSurface(pTempSurface);
    
    SDL_QueryTexture(m_pTexture1, NULL, NULL,
        &m_sourceRectangle1.w, &m_sourceRectangle1.h);

    SDL_QueryTexture(m_pTexture, NULL, NULL,
    &m_sourceRectangle.w, &m_sourceRectangle.h);


    m_destinationRectangle1.w = m_sourceRectangle1.w;
    m_destinationRectangle1.h = m_sourceRectangle1.h;

    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    m_destinationRectangle1.x = m_sourceRectangle1.x = 0;
    m_destinationRectangle1.y = m_sourceRectangle1.y = 0;

    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;

    m_bRunning = true;
    return true;
}

void Game::update()
{

}

void Game::render()
{
    const int chgWay_Max = 640 - m_destinationRectangle.w;
    SDL_RenderClear(m_pRenderer);
    SDL_RenderCopy(m_pRenderer, m_pTexture1, &m_sourceRectangle, &m_destinationRectangle);
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