#include "bird.hpp"

#include <stddef.h>
#include <algorithm>

#include "drawing.hpp"
#include "globals.hpp"

#define sgn(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))

const float Bird::Width = 256.0f;
const float Bird::Height = 256.0f;

Bird::Bird()
: Entity(), gravity(), vel(), textureId(0), r(1), g(1), b(1)
{ LoadResources(); }

Bird::Bird(const Vector2f &pos)
: Entity(pos), gravity(), vel(), textureId(0), r(1), g(1), b(1)
{ LoadResources(); }

Bird::Bird(const Vector2f &pos, const Vector2f &gravity)
: Entity(pos), gravity(gravity), vel(), textureId(0), r(1), g(1), b(1)
{ LoadResources(); }

Bird::~Bird()
{
  FreeResources();
}

void Bird::LoadResources()
{
  textureId = Globals::LoadTexture("./app/native/assets/Kappa.png", NULL, NULL);
}

void Bird::FreeResources()
{
  Globals::DeleteTexture(textureId);
}

void Bird::Update()
{
  vel += gravity * Globals::DeltaTime;
  /*vel.y = std::min(std::abs(vel.y), 20.0f);*/
  if(std::abs(vel.y) > 20.0f) vel.y = 20.0f * sgn(vel.y);

  pos += vel * Globals::DeltaTime;
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
