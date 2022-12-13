#include "TextureManager.h"
#include "SDL_image.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(string fileName, string id, SDL_Renderer* pRenderer)
{
  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
  if(pTempSurface == 0)
  {
    return false; // �̹��� �ε� ����
  }

  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
  if(pTexture == 0)
  {
    return false; // �ؽ��� ���� ����
  }
  SDL_FreeSurface(pTempSurface);

  m_textureMap[id] = pTexture;

  return true;
}

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  // �������� ����
  srcRect.x = width * currentFrame; // ���� x��ǥ
  srcRect.y = height * currentRow; // ���� y��ǥ
  srcRect.w = width; // �ʺ�
  srcRect.h = height; // ����

  // ������ ����
  destRect.x = x; // ���� x��ǥ
  destRect.y = y; // ���� y��ǥ
  destRect.w = width; // �ʺ�
  destRect.h = height; // ����

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, NULL, flip);
}