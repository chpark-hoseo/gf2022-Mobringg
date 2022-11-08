#pragma once

#include "GameObject.h"

class Monster : public GameObject
{
public:
    void load(int x, int y, int width, int height, std::string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update(int speed);
    void clean() {};

private:
    bool face = 1; //x방향 좌우값 초기화
    int speed = 1; //몬스터 스피드 설정을 위한 초기화
};

