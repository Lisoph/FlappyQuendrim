#pragma once

#include "entity.hpp"
#include "pipe.hpp"

#include <vector>

class Bird;

class Level: public Entity
{
private:
  std::vector<Pipe*> pipes;
  int scroll;
public:
  Level(unsigned int seed);
  virtual ~Level();

  virtual void Update();
  virtual void Draw();

  bool BirdCollidesWithPipe(Bird *bird, Pipe *pipe) const;
  bool BirdCollides(Bird *bird) const;
};
