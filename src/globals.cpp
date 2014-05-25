#include "globals.hpp"

#include <cstdlib>

#include "bbutil.h"
#include <GLES/gl.h>

float Globals::DeltaTime = 1.0f;
unsigned Globals::FPS = 0;

float Globals::ScreenWidth = 0.0f;
float Globals::ScreenHeight = 0.0f;

unsigned int Globals::LoadTexture(const char *file, int *width, int *height)
{
  unsigned int texId;

  int ret = bbutil_load_texture(file, width, height, NULL, NULL, &texId);
  if(ret == EXIT_SUCCESS)
    return texId;
  return 0;
}

void Globals::DeleteTexture(unsigned int texture)
{
  glDeleteTextures(1, &texture);
}
