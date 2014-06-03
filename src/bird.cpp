#include "bird.hpp"

#include <stddef.h>
#include <algorithm>

#include "drawing.hpp"
#include "globals.hpp"
#include "level.hpp"

#define sgn(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))

const float Bird::Width = 256.0f;
const float Bird::Height = 256.0f;

Bird::Bird(Level *level)
: Entity(), gravity(), vel(), textureId(0), level(level), r(1), g(1), b(1)
{ LoadResources(); }

Bird::Bird(const Vector2f &pos, Level *level)
: Entity(pos), gravity(), vel(), textureId(0), level(level), r(1), g(1), b(1)
{ LoadResources(); }

Bird::Bird(const Vector2f &pos, const Vector2f &gravity, Level *level)
: Entity(pos), gravity(gravity), vel(), textureId(0), level(level), r(1), g(1), b(1)
{ LoadResources(); }

Bird::~Bird()
{
  FreeResources();
}

void Bird::LoadResources()
{
  textureId = Globals::LoadTexture("./app/native/assets/quendrim2.png", NULL, NULL);
}

void Bird::FreeResources()
{
  Globals::DeleteTexture(textureId);
}

void Bird::Update()
{
  vel += gravity * Globals::DeltaTime;
  if(std::abs(vel.y) > 20.0f) vel.y = 20.0f * sgn(vel.y);

  pos += vel * Globals::DeltaTime;

  /* -------------------------------------------------------------------- */

  if(level->BirdCollides(this))
  {
    /*r = 1.0f;
    g = 0.0f;
    b = 0.0f;*/

    Respawn();
  }
  else
  {
    r = g = b = 1.0f;
  }
}

void Bird::Draw()
{
  Drawing::DrawSprite(textureId, pos.x, pos.y, Width, Height, r, g, b);
}

void Bird::OnScreenTouch()
{
  if(vel.y < 0) vel.y = 0;
  vel += Vector2f(0.0f, 15.0f); /* Pretty good */
}

void Bird::Respawn()
{
  level->Reset();

  vel = pos = Vector2f();
}
