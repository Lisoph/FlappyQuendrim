#pragma once

namespace Globals
{
  extern float DeltaTime;
  extern unsigned FPS;

  extern float ScreenWidth;
  extern float ScreenHeight;

  unsigned int LoadTexture(const char *file, int *width, int *height);
  void DeleteTexture(unsigned int texture);
}

/*namespace Globals
{

}*/
