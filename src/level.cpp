#include "level.hpp"

#include <cstdlib>
#include "globals.hpp"

Level::Level(unsigned int seed)
: pipes(), scroll(100.0f)
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
  /* I have no idea what's going on here. It's way too late anyways, way too tired to think. */
  /* Gn8 */

  scroll += 1.0f * Globals::DeltaTime;
  if(scroll > 100) scroll -= 100;

  if((int)scroll % 100 == 0)
  {
    //pipes.push_back(new Pipe(Vector2f(Globals::ScreenWidth * 0.5f + Pipe::Width * 0.5f, 0.0f)));
    pipes.push_back(new Pipe(Vector2f(2.0f, 0.0f)));
  }

  for(std::vector<Pipe*>::iterator it = pipes.begin(); it != pipes.end(); ++it)
  {
    Pipe *pipe = *it;

    //pipe->pos.x -= scroll * Globals::DeltaTime;
    pipe->SetPos(pipe->Pos() - Vector2f(0.01, 0.0f));

    /* Check if a pipe is beyond the far left, if so delete it */
    if(pipe->Pos().x < -Globals::ScreenWidth * 0.5f /*+ Pipe::Width * 0.5f*/)
    {
      pipes.erase(it);
      delete pipe;
    }
  }
}

void Level::Draw()
{
  for(std::vector<Pipe*>::iterator it = pipes.begin(); it != pipes.end(); ++it)
    (*it)->Draw();
}
