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

    
    
 
    if (!TheTextureManager::Instance()->load("assets/145.bmp", "Chr", m_pRenderer))
    {
        return false;
    }
    if (!TheTextureManager::Instance()->load("assets/456.png", "Wall", m_pRenderer))
    {
        return false;
    }
    int world[10][10] = {
       { 1,1,1,1,1,1,1,1,1,1 },
       { 1,2,1,0,0,0,0,0,0,1 },
       { 1,0,1,0,0,0,0,1,0,1 },
       { 1,0,0,1,0,0,0,1,0,1 },
       { 1,0,0,1,0,0,0,0,0,1 },
       { 1,0,0,0,0,1,1,0,0,1 },
       { 1,0,0,0,0,1,1,0,0,1 },
       { 1,0,0,0,0,0,0,0,0,1 },
       { 1,0,0,0,0,1,1,0,0,1 },
       { 1,1,1,1,1,1,1,1,1,1 },

    };
    int x = 0;
    int y = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (world[i][j] == 1)
            {
                wall[10 * i + j].u = x; wall[10 * i + j].d = y; wall[10 * i + j].l = TILE_SIZE; wall[10 * i + j].r = TILE_SIZE;
            }
            else if (world[i][j] == 2)
            {
                alpha_x = i * 90;
                alpha_y = j * 90;

                // wallDes.u = x; wallDes.d = y; wallDes.l = TILE_SIZE; wallDes.r = TILE_SIZE;
            }
            x += TILE_SIZE;
        }
        x = 0;
        y += TILE_SIZE;
    }
    m_bRunning = true;
    return true;

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "Chr")));
    //m_gameObjects.push_back(new Enemy(new LoaderParams(300, 100, 128, 82, "animate")));

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
    SDL_RenderClear(m_pRenderer);

    for (int i = 0; i < collisionCount; i++)
    {
        TheTextureManager::Instance()->draw("Wall", wall[i].u, wall[i].d, wall[i].l, wall[i].r, m_pRenderer);
    }
    if (alphaS == 1)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x,alpha_y, 50, 50, 0, m_currentFrame, m_pRenderer);
    else if (alphaS == 2)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 1, m_currentFrame, m_pRenderer);
    else if (alphaS == 3)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 2, m_currentFrame, m_pRenderer);
    else if (alphaS == 4)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 3, m_currentFrame, m_pRenderer);
    
  
    SDL_RenderPresent(m_pRenderer);
    
}

bool Game::running()
{
    return m_bRunning;
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