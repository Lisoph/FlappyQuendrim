#include "game.hpp"
#include <GLES/gl.h>

#include "globals.hpp"

void Game::Init()
{
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const float halfWidth = Globals::ScreenWidth / 2;
  const float halfHeight = Globals::ScreenHeight / 2;
  glOrthof(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
}

void Game::Update()
{

}

void Game::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
}

void Game::Fina()
{

}
