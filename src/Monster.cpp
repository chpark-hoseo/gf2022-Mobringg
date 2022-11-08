#include "Monster.h"

void Monster::load(int x, int y, int width, int height, std::string textureID)
{
	GameObject::load(x, y, width, height, textureID);
}

void Monster::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
}

void Monster::update(int speed)
{
	
	m_currentFrame = ((SDL_GetTicks() / 100) % 6);
	//스크린 사이즈에 맞게 좌우 끝에 도달시 반대 방향으로 이동
	if(face == 1)
	{
		m_x += speed;
		if (m_x > 400)
			face = 0;
}
	else if (face == 0)
	{
		m_x -= speed;
		if (m_x < 0)
			face = 1;
	}


}