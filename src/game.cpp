#include "game.hpp"
#include <GLES/gl.h>
#include <cstdlib>

#include "globals.hpp"

#include "bbutil.h"

int LoadTexture(const char *file, int *width, int *height)
{
  unsigned int texId;

  int ret = bbutil_load_texture(file, width, height, NULL, NULL, &texId);
  if(ret == EXIT_SUCCESS)
    return texId;
  return 0;
}

float spriteX = 0.0f, spriteY = 0.0f;

void DrawSprite(unsigned int texture, float x, float y, float w, float h)
{
  float vertices[] =
  {
    -0.5f * w, 0.5f * h,
    -0.5f * w, -0.5f * h,
    0.5f * w, 0.5f * h,
    0.5f * w, -0.5f * h
  };

  static float texCoords[] =
  {
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
  };

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glPushMatrix();

  //glScalef(w, h, 0.0f);
  //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glTranslatef(x, y, 0.0f);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glPopMatrix();

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

unsigned int myTexture = 0;


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

  myTexture = LoadTexture("./app/native/assets/Kappa.png", NULL, NULL);
}

void Game::Update()
{

}

void Game::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  if(myTexture > 0)
    DrawSprite(myTexture, spriteX, spriteY, 512.0f, 512.0f);
}

void Game::Fina()
{
  glDeleteTextures(1, &myTexture);
}

void Game::OnScreenTouch(int x, int y)
{
  /* Translate screen coordinates to game coordinates */
  float trueX = x - Globals::ScreenWidth * 0.5f;
  float trueY = Globals::ScreenHeight * 0.5f - y;

  spriteX = trueX;
  spriteY = trueY;
}
