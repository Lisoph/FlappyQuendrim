#pragma once

#include "entity.hpp"
#include "pipe.hpp"
#include "bird.hpp"

#include <vector>

class Level: public Entity
{
private:
  std::vector<Pipe*> pipes;
  int scroll;
  Bird *bird;
public:
  Level(unsigned int seed, Bird *bird);
  virtual ~Level();

  virtual void Update();
  virtual void Draw();
};
