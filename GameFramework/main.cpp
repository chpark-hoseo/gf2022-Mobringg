// ���۹�
// �¿� ����Ű : ���鿡�� �̵�, ���� �� ���� ����
// �����̽� �� : ������ �� ������ ���� ������ ����
// ���콺 ���� Ŭ�� : ���콺 ��ġ�� �Ѿ� �߻�(�÷��� �� �ʼ������� ����)

// �߰��� ���� ����
// Background.cpp, h : ���
// Bullet.cpp, h : �Ѿ�
// Camera.cpp, h : ȭ�齺ũ�� ������ ���� ī�޶� ����
// CollisionManager.cpp, h : �浹 ���θ� ��ȯ���ִ� ��ü
// Goal.cpp, h : Ŭ��� ���� ������ǥ����
// Player.cpp, h : �÷��̾�
// UI.cpp, h : UI
// UIClearTime.cpp, h : Ŭ����Ÿ��
// UIManager. cpp, h : ��Ʈ �ʱ�ȭ�� UI�� �׷��ִ� ��ü
// Wall.cpp, h : ��

// ������ �ڵ� ����
// SDLGameObject. cpp : ȭ�齺ũ�� ������ ���� draw() ����

#include <iostream>
#include "Game.h"

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 540;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
    if (TheGame::Instance()->init("Chapter 1", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, false) == false)
    {
        cout << "game init failure" << SDL_GetError() << endl;

        return 1;
    }

    Uint32 frameStart, frameTime;

    while( TheGame::Instance()->running() )
    {
        frameStart = SDL_GetTicks();

        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update();
        TheGame::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;
    
        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    TheGame::Instance()->clean();

    return 0;
}