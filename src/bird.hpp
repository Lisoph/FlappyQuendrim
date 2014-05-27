#pragma once

#include "entity.hpp"

class Level;

class Bird: public Entity
{
public:
  static const float Width;
  static const float Height;
private:
  Vector2f gravity;
  Vector2f vel;
  unsigned int textureId;
  Level *level;
public:
  const Vector2f &Gravity() const { return gravity; }
  void SetGravity(const Vector2f &gravity) { this->gravity = gravity; }

  float r, g, b;

  Bird(Level *level);
  Bird(const Vector2f &pos, Level *level);
  Bird(const Vector2f &pos, const Vector2f &gravity, Level *level);
  virtual ~Bird();

  void LoadResources();
  void FreeResources();

  virtual void Update();
  virtual void Draw();

  void OnScreenTouch();
};
