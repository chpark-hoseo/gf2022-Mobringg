#include "Goal.h"
#include "CollisionManager.h"
#include "Camera.h"

Goal* Goal::s_pInstance = 0;

void Goal::draw()
{
	// ȭ�� �ȿ� ���� ��
	if (TheCollisionManager::Instance()->isCollisionSquareToSquare(m_position.getX(), m_position.getX() + getWidth(), m_position.getY(), m_position.getY() + getHeight(),
		TheCamera::Instance()->getLeft(), TheCamera::Instance()->getRight(), TheCamera::Instance()->getTop(), TheCamera::Instance()->getBottom()))
		SDLGameObject::draw();
}