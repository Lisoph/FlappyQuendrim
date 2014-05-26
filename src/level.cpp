#include "level.hpp"

#include <cstdlib>

#include "globals.hpp"
#include "bird.hpp"

#include <GLES/gl.h>

Level::Level(unsigned int seed, Bird *bird)
: pipes(), scroll(0), bird(bird)
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
  //bird->SetPos(Vector2f());

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

    /* Collision detection */
    /*float pipeLeft = pipe->Pos().x - pipe->Width() * 0.5f;
    float pipeRight = pipe->Pos().x + pipe->Width() * 0.5f;
    float pipeTop = pipe->Pos().y + pipe->Height() * 0.5f;
    float pipeBottom = pipe->Pos().y - pipe->Height() * 0.5f;

    float birdLeft = bird->Pos().x - Bird::Width * 0.5f;
    float birdRight = bird->Pos().x + Bird::Width * 0.5f;
    float birdTop = bird->Pos().y + Bird::Height * 0.5f;
    float birdBottom = bird->Pos().y - Bird::Height * 0.5f;

   if(birdLeft < pipeRight && birdRight > pipeLeft && birdTop > pipeBottom && birdBottom < pipeTop)
   {
     bird->r = 1.0f;
     bird->g = 0.0f;
     bird->b = 0.0f;
   }
   else
   {
     bird->r = 1.0f;
     bird->g = 1.0f;
     bird->b = 1.0f;
   }*/
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

#if 0
  float birdLeft = bird->Pos().x - Bird::Width * 0.5f;
  float birdRight = bird->Pos().x + Bird::Width * 0.5f;
  float birdTop = bird->Pos().y + Bird::Height * 0.5f;
  float birdBottom = bird->Pos().y - Bird::Height * 0.5f;

  float vertices[] =
  {
    birdLeft, birdTop,
    birdLeft, birdBottom,
    birdRight, birdTop,
    birdRight, birdBottom
  };

  glDisable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);

  glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
  glEnable(GL_TEXTURE_2D);
#endif
}
