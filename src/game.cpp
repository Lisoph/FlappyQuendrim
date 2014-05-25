#include "game.hpp"
#include <GLES/gl.h>

#include <vector>

#include "globals.hpp"
#include "bbutil.h"

#include "bird.hpp"
#include "level.hpp"

float spriteX = 0.0f, spriteY = 0.0f;
std::vector<Entity*> entities;

Bird *bird = NULL;
Level *level = NULL;

void Game::Init()
{
  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const float halfWidth = Globals::ScreenWidth / 2;
  const float halfHeight = Globals::ScreenHeight / 2;
  glOrthof(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_TEXTURE_2D);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Bird */
  bird = new Bird(Vector2f(0.0f, 0.0f), Vector2f(0.0f, -0.001f));
  entities.push_back(bird);

  level = new Level(1234);
  entities.push_back(level);
}

void Game::Update()
{
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    (*it)->Update();
}

void Game::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
      (*it)->Draw();
}

void Game::Fina()
{
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    delete *it;
}

void Game::OnScreenTouch(int x, int y)
{
  /* Translate screen coordinates to game coordinates */
  float trueX = x - Globals::ScreenWidth * 0.5f;
  float trueY = Globals::ScreenHeight * 0.5f - y;

  spriteX = trueX;
  spriteY = trueY;

  bird->OnScreenTouch();
}
