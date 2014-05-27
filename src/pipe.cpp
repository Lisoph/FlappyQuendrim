#include "pipe.hpp"

//#include <stddef.h>
#include <cstdlib>
#include <algorithm>

#include "globals.hpp"
#include "drawing.hpp"

unsigned int Pipe::textureId = 0;

Pipe::Pipe()
:Entity(), /*textureId(0),*/ width(64.0f), height(512.0f)
{ /*LoadResources();*/ }

Pipe::Pipe(const Vector2f &pos)
: Entity(pos), /*textureId(0),*/ width(64.0f), height(512.0f)
{ /*LoadResources();*/ }

Pipe::Pipe(float width, float height)
: Entity(), /*textureId(0),*/ width(width), height(height)
{ /*LoadResources();*/ }

Pipe::Pipe(const Vector2f &pos, float width, float height)
: Entity(pos), /*textureId(0),*/ width(width), height(height)
{ /*LoadResources();*/ }

Pipe::~Pipe()
{
  /*FreeResources();*/
}

void Pipe::LoadResources()
{
  textureId = Globals::LoadTexture("./app/native/assets/test.png", NULL, NULL);
}

void Pipe::FreeResources()
{
  Globals::DeleteTexture(textureId);
}

void Pipe::Draw()
{
  Drawing::DrawSprite(textureId, pos.x, pos.y, width, height);
}

/* ---------------------------------------------------------------------------------------- */

Pipe *RandomPipe()
{
  static PipeType pipeTypes[] =
  {
    PipeType(Globals::ScreenHeight * 0.25f, 64.0f, Globals::ScreenHeight * 0.5f),
    PipeType(Globals::ScreenHeight * -0.25f, 64.0f, Globals::ScreenHeight * 0.5f),
  };

  Pipe *newPipe = new Pipe();

  const PipeType &pt = pipeTypes[std::min(std::rand() % (sizeof(pipeTypes) / sizeof(pipeTypes[0])), sizeof(pipeTypes) / sizeof(pipeTypes[0]) - 1)];
  newPipe->SetSize(pt.width, pt.height);
  newPipe->SetPos(Vector2f(0.0f, pt.y));

  return newPipe;
}
