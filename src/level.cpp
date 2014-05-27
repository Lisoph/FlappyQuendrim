#include "level.hpp"

#include <cstdlib>

#include "globals.hpp"
#include "bird.hpp"

#include <GLES/gl.h>

Level::Level(unsigned int seed)
: pipes(), scroll(0)
{
  std::srand(seed);
}

Level::~Level()
{
  for(std::vector<Pipe*>::iterator it = pipes.begin(); it != pipes.end(); ++it)
    delete *it;

  pipes.clear();
}

void Level::Update()
{
  if(++scroll > 1000) scroll = 1;

  if(scroll % (int)(Bird::Width * 0.75) == 0)
  {
    Pipe *newPipe = RandomPipe();
    newPipe->SetPos(newPipe->Pos() + Vector2f(Globals::ScreenWidth * 0.5f + newPipe->Width() * 0.5f, 0.0f));

    pipes.push_back(newPipe);
  }

  static std::vector<std::vector<Pipe*>::iterator> toErase;
  toErase.clear();

  for(std::vector<Pipe*>::iterator it = pipes.begin(); it != pipes.end(); ++it)
  {
    Pipe *pipe = *it;

    pipe->SetPos(pipe->Pos() - Vector2f(2 * Globals::DeltaTime, 0.0f));

    /* Check if a pipe is beyond the far left, if so delete it */
    if(pipe->Pos().x < -Globals::ScreenWidth * 0.5f - pipe->Width() * 0.5f)
    {
      toErase.push_back(it);
      delete pipe;
    }
  }

  for(std::vector<std::vector<Pipe*>::iterator>::iterator it = toErase.begin(); it != toErase.end(); ++it)
  {
    pipes.erase(*it);
  }
}

void Level::Draw()
{
  for(std::vector<Pipe*>::iterator it = pipes.begin(); it != pipes.end(); ++it)
    (*it)->Draw();
}

bool Level::BirdCollidesWithPipe(Bird *bird, Pipe *pipe) const
{
  float pipeLeft = pipe->Pos().x - pipe->Width() * 0.5f;
  float pipeRight = pipe->Pos().x + pipe->Width() * 0.5f;
  float pipeTop = pipe->Pos().y + pipe->Height() * 0.5f;
  float pipeBottom = pipe->Pos().y - pipe->Height() * 0.5f;

  float birdLeft = bird->Pos().x - Bird::Width * 0.5f;
  float birdRight = bird->Pos().x + Bird::Width * 0.5f;
  float birdTop = bird->Pos().y + Bird::Height * 0.5f;
  float birdBottom = bird->Pos().y - Bird::Height * 0.5f;

 if(birdLeft < pipeRight && birdRight > pipeLeft && birdTop > pipeBottom && birdBottom < pipeTop)
   return true;
 return false;
}

bool Level::BirdCollides(Bird *bird) const
{
  for(std::vector<Pipe*>::const_iterator it = pipes.begin(); it != pipes.end(); ++it)
  {
    if(BirdCollidesWithPipe(bird, *it))
      return true;
  }

  return false;
}
