#include "Player.h"
#include "InputHandler.h"
#include "Game.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);
    m_currentFrame = ((SDL_GetTicks() / 100) % 6);
	handleInput();
	SDLGameObject::update();

}

void Player::handleInput()
{
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        alphaS = 1;
        
        m_velocity.setX(2);
        m_currentFrame = ((SDL_GetTicks() / 100) % 6);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
        alphaS = 2;
        
        m_velocity.setX(-2);
        m_currentFrame = ((SDL_GetTicks() / 100) % 6);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
        alphaS = 3;
        
        m_velocity.setY(-2);
        m_currentFrame = ((SDL_GetTicks() / 100) % 6);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
        alphaS = 4;
        ;
        m_velocity.setY(2);
        m_currentFrame = ((SDL_GetTicks() / 100) % 6);
    }
}


void Player::clean() {}
