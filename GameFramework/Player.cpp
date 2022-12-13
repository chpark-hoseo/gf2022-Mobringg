#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "CollisionManager.h"
#include "Goal.h"

Player* Player::s_pInstance = 0;

void Player::draw()
{
  SDLGameObject::draw(flip);
}

void Player::update()
{
  handleInput();
  checkCollision();
  updateSprite();

  SDLGameObject::update();
}

void Player::handleInput()
{
    // ������ ��� ���� ��
    if (onGround == true)
    {
        // �����̽� �ٸ� ������
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
            m_velocity.setX(0);

            // ������ �� 1������
            if (temp_SPACEBAR)
            {
                temp_SPACEBAR = false;
                jumpingPower = (float)SDL_GetTicks();
            }
        }
        // �����̽� �ٸ� ������ ������
        else
        {
            // ���� �� 1������
            if (!temp_SPACEBAR)
            {
                temp_SPACEBAR = true;

                jumpingPower = (float)((SDL_GetTicks() - jumpingPower)/1000); // �����ð� 1�ʴ� 1

                // ������ �ִ� ����
                if (jumpingPower > 1)
                    jumpingPower = 1.0;

                m_velocity.setY(-7.5 * jumpingPower);
                onGround = false;
                setGravity();

                // ���� ����
                if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
                {
                    m_velocity.setX(-jumpSpeed);
                }
                else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
                {
                    m_velocity.setX(jumpSpeed);
                }
                else
                {
                    m_velocity.setX(0);
                }
            }
            // ���� ������ �̵�
            else
            {
                // ���׼�����
                if (!(m_velocity.getX() == jumpSpeed) && !(m_velocity.getX() == -jumpSpeed))
                {
                    // �¿� �̵�
                    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
                    {
                        m_velocity.setX(-groundSpeed);
                    }
                    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
                    {
                        m_velocity.setX(groundSpeed);
                    }
                    else
                    {
                        m_velocity.setX(0);
                    }
                }
            }
        }
    }
    // ���߿���
    else
    {
        // ���� ����
        m_velocity.setX(m_velocity.getX() * 0.99);
    }

    // ���콺 ���� ������ �� 1������
    if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && temp_MOUSEBUTTONLEFT)
    {
        temp_MOUSEBUTTONLEFT = false;

        int bulletWidth = 20;
        int bulletHeight = 20;
        TheGame::Instance()->createBulletObject(m_position.getX()+m_width/2 - bulletWidth/2, m_position.getY()+m_height/2 - bulletHeight/2, bulletWidth, bulletHeight);
    }
    // ���콺 ���� ���� �� 1������
    else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && !temp_MOUSEBUTTONLEFT)
    {
        temp_MOUSEBUTTONLEFT = true;
    }
}

// ���ϼӵ� ����
void Player::setGravity()
{
    m_acceleration.setY(0.15);

    // ���� �ִ�ӵ� ����
    if (m_velocity.getY() > 7.5)
        m_velocity.setY(7.5);
}

void Player::checkCollision()
{
    int playerLeft = m_position.getX();
    int playerRight = playerLeft + m_width;
    int playerTop = m_position.getY();
    int playerBottom = playerTop + m_height;

    int count = 0;

    //���� �浹 ��
    for (int i = 0; i < TheGame::Instance()->getWallObjects().size(); i++)
    {
        int objectLeft = TheGame::Instance()->getWallObjects()[i]->getPosition().getX();
        int objectRight = objectLeft + TheGame::Instance()->getWallObjects()[i]->getWidth();
        int objectTop = TheGame::Instance()->getWallObjects()[i]->getPosition().getY();
        int objectBottom = objectTop + TheGame::Instance()->getWallObjects()[i]->getHeight();

        // �浹 ��
        if (TheCollisionManager::Instance()->isCollisionSquareToSquare(playerLeft, playerRight, playerTop, playerBottom,
            objectLeft, objectRight, objectTop, objectBottom))
        {
            // �Ʒ�����
            if (m_velocity.getY() > 0 && playerBottom >= objectTop && playerBottom <= objectTop + m_velocity.getY())
            {
                m_position.setY(objectTop - m_height);
                playerTop = m_position.getY();
                playerBottom = playerTop + m_height;

                m_velocity.setY(0);
                m_acceleration.setY(0.0);
            }
            // ������
            else if (m_velocity.getY() < 0 && playerTop <= objectBottom && playerTop >= objectBottom + m_velocity.getY())
            {
                m_position.setY(objectBottom);
                playerTop = m_position.getY();
                playerBottom = playerTop + m_height;

                m_velocity.setY(0);

                if (!onGround)
                    m_velocity.setX(m_velocity.getX() * 1 / 2);
            }

            // �޹���
            if (m_velocity.getX() < 0 && playerLeft <= objectRight && playerLeft > objectLeft && playerTop != objectBottom && playerBottom != objectTop)
            {
                m_position.setX(objectRight);

                horizontalCollision();
            }
            // ��������
            else if (m_velocity.getX() > 0 && playerRight >= objectLeft && playerRight < objectRight && playerTop != objectBottom && playerBottom != objectTop)
            {
                m_position.setX(objectLeft - m_width);

                horizontalCollision();
            }

            // ������ ��� ���� ��
            if (playerBottom == objectTop)
            {
                count++;
                onGround = true;
            }
        }
    }

    // ������ ������� ���� ��
    if (count == 0)
    {
        setGravity();
        onGround = false;
    }

    // ȭ�� �¿��� �浹
    if (m_velocity.getX() < 0 && TheCollisionManager::Instance()->isCollisionSquareToVerticalLine(playerLeft, playerRight, TheCamera::Instance()->getLeft()))
    {
        m_position.setX(0);

        horizontalCollision();
    }
    else if (m_velocity.getX() > 0 && TheCollisionManager::Instance()->isCollisionSquareToVerticalLine(playerLeft, playerRight, TheCamera::Instance()->getRight()))
    {
        m_position.setX(TheGame::Instance()->getWindowWidth() - m_width);

        horizontalCollision();
    }

    // ������ǥ������ �浹 ��
    if (TheCollisionManager::Instance()->isCollisionSquareToSquare(playerLeft, playerRight, playerTop, playerBottom,
        TheGoal::Instance()->getPosition().getX(), TheGoal::Instance()->getPosition().getX() + TheGoal::Instance()->getWidth(), TheGoal::Instance()->getPosition().getY(), TheGoal::Instance()->getPosition().getY() + TheGoal::Instance()->getHeight()))
    {
        // ���� ����
        TheGame::Instance()->quit();
    }
}

// ���� �浹ó��
void Player::horizontalCollision()
{
    if (onGround)
        m_velocity.setX(0);
    else
        m_velocity.setX(m_velocity.getX() * -1 / 2);
}

// ��������Ʈ ����
void Player::updateSprite()
{
  if(m_velocity.getX() < 0)
  {
    m_currentFrame = (frameCount++ / 6 + 1) % 6;
    flip = SDL_FLIP_HORIZONTAL;
  }
  else if(m_velocity.getX() > 0)
  {
    m_currentFrame = (frameCount++ / 6 + 1) % 6;
    flip = SDL_FLIP_NONE;
  }
  else
  {
    m_currentFrame = 0;
    frameCount = 0;
  }
}