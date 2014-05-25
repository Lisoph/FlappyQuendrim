#include "bird.hpp"

#include <stddef.h>
#include <algorithm>

#include "drawing.hpp"
#include "globals.hpp"

Bird::Bird()
:Entity(), gravity(), vel(), textureId(0)
{ LoadResources(); }

Bird::Bird(const Vector2f &pos)
: Entity(pos), gravity(), vel(), textureId(0)
{ LoadResources(); }

Bird::Bird(const Vector2f &pos, const Vector2f &gravity)
: Entity(pos), gravity(gravity), vel(), textureId(0)
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
  vel += gravity;
  vel.x = std::min(vel.x, 0.06f);
  vel.y = std::min(vel.y, 0.06f);

  pos += vel * Globals::DeltaTime;
}

void Bird::Draw()
{
  Drawing::DrawSprite(textureId, pos.x, pos.y, 256.0f, 256.0f);
}

void Bird::OnScreenTouch()
{
  if(vel.y < 0) vel.y = 0;
  vel += Vector2f(0.0f, 0.05f); /* Pretty good */
}
