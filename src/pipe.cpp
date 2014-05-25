#include "pipe.hpp"

#include <stddef.h>

#include "globals.hpp"
#include "drawing.hpp"

float Pipe::Width = 64.0f;
float Pipe::Height = 256.0f;

Pipe::Pipe()
:Entity(), textureId(0)
{ LoadResources(); }

Pipe::Pipe(const Vector2f &pos)
: Entity(pos), textureId(0)
{ LoadResources(); }

Pipe::~Pipe()
{
  FreeResources();
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
  Drawing::DrawSprite(textureId, pos.x, pos.y, Width, Height);
}
