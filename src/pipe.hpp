#pragma once

#include "entity.hpp"

class Pipe: public Entity
{
private:
  static unsigned int textureId;
  float width, height;
public:
public:
  float Width() { return width; }
  float Height() { return height; }
  void SetSize(float width, float height) { this->width = width; this->height = height; }

  Pipe();
  Pipe(const Vector2f &pos);
  Pipe(float width, float height);
  Pipe(const Vector2f &pos, float width, float height);
  virtual ~Pipe();

  static void LoadResources();
  static void FreeResources();

  //virtual void Update();
  virtual void Draw();
};

struct PipeType
{
  float y;
  float width, height;

  PipeType(float y, float width, float height)
  : y(y), width(width), height(height)
  {}
};

Pipe *RandomPipe();
