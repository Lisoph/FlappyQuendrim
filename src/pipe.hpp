#pragma once

#include "entity.hpp"

class Pipe: public Entity
{
private:
  unsigned int textureId;
public:
  static float Width;
  static float Height; // Static for now
public:
  Pipe();
  Pipe(const Vector2f &pos);
  virtual ~Pipe();

  void LoadResources();
  void FreeResources();

  //virtual void Update();
  virtual void Draw();
};
