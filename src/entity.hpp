#pragma once

#include "vector2.hpp"

class Entity
{
protected:
  Vector2f pos, rot;
public:
  const Vector2f &Pos() const { return pos; }
  void SetPos(const Vector2f &pos) { this->pos = pos; }

  const Vector2f &Rot() const { return rot; }
  void SetRot(const Vector2f &rot) { this->pos = rot; }

  Entity(void)
  : pos(), rot()
  {}
  Entity(const Vector2f &pos)
  : pos(pos), rot()
  {}
  Entity(const Vector2f &pos, const Vector2f &rot)
  : pos(pos), rot(rot)
  {}
  virtual ~Entity() {}

  virtual void Update() {}
  virtual void Draw() {}
};
