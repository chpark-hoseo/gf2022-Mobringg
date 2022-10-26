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
                return false; // ������ ���� ����
            }
        }
        else {
            return false; // ������ ���� ����
        }
    }
    else {
        return false; // SDL �ʱ�ȭ ����
    };

 //ĳ���� �̹��� �ҷ�����
    if (!TheTextureManager::Instance()->load("assets/145.bmp", "Chr", m_pRenderer)) //��������Ʈ �̹��� ��� ����ȭ �ʿ� - �ذ����
    {
        return false;
    }
//�� �̹��� �ҷ�����
    if (!TheTextureManager::Instance()->load("assets/456.png", "Wall", m_pRenderer))
    {
        return false;
    }

//��(��ó:https://www.parallelrealities.co.uk/tutorials/sdl1/intermediate/tutorial11.php
http://lazyfoo.net/tutorials/SDL/39_tiling/index.php
https://bikim0108.tistory.com/32)

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
}
    


//ĳ���� ��������Ʈ �ӵ�
void Game::update()
{
    chr();
    m_currentFrame = ((SDL_GetTicks() / 100) % 5);
    SDL_Delay(5);
    
}

//ĳ���Ͱ� Ű�Է��� �޾� �����̴� �ڵ�
void Game::chr()
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
    else if (currentKeyStates[SDL_SCANCODE_ESCAPE]) // ESC�Է½� ���� ����
    {
        m_bRunning = false;
    }
}


//ĳ���Ͱ� �����ϴ� ���⿡ ���� �˸´� ��������Ʈ �̹��� ����
void Game::render()
{
    
    SDL_RenderClear(m_pRenderer);
    for (int i = 0; i < collisionCount; i++)
    {
        TheTextureManager::Instance()->draw("Wall", wall[i].u, wall[i].d, wall[i].l, wall[i].r, m_pRenderer);
    }

    
    
    if (alphaS == 1)
        TheTextureManager::Instance()->drawFrame("Chr", alpha_x, alpha_y, 50, 50, 0, m_currentFrame, m_pRenderer);
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