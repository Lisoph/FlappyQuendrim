#pragma once

#include "entity.hpp"
#include "pipe.hpp"

#include <vector>

class Level: public Entity
{
private:
  std::vector<Pipe*> pipes;
  float scroll;
public:
  Level(unsigned int seed);
  virtual ~Level();

  virtual void Update();
  virtual void Draw();
};
