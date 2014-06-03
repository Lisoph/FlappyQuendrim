#pragma once

#include "entity.hpp"
#include "pipe.hpp"

#include <vector>

#define LEVEL_DEFAULT_SPEED 2

class Bird;

class Level: public Entity
{
private:
  unsigned int seed;
  std::vector<Pipe*> pipes;
  int scroll;
  float speed;
public:
  Level(unsigned int seed);
  virtual ~Level();

  virtual void Update();
  virtual void Draw();

  bool BirdCollidesWithPipe(Bird *bird, Pipe *pipe) const;
  bool BirdCollides(Bird *bird) const;

  void Reset();
};
