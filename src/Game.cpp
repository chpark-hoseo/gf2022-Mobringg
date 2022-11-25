#include "Game.h"
#include "InputHandler.h"
#pragma once

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        m_pWindow = SDL_CreateWindow(
            title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(
                    m_pRenderer, 255, 0, 0, 255);
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

    

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 100, 128, 82, "animate")));

    m_bRunning = true;
    return true;
}

Game* Game::s_pInstance = 0;

void Game::update()
{
    for (int i = 0;  i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
    m_currentFrame = ((SDL_GetTicks() / 100) % 6);
    
}



void Game::render()
{
    
    SDL_RenderClear(m_pRenderer);
    
    for (int i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
  
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

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}

void Game::clean() 
{
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}