#include "drawing.hpp"

#include <GLES/gl.h>

void Drawing::DrawSprite(unsigned int texture, float x, float y, float w, float h, float r, float g, float b)
{
  static float vertices[] =
  {
    -0.5f, 0.5f,
    -0.5f, -0.5f,
    0.5f, 0.5f,
    0.5f, -0.5f
  };

  static float texCoords[] =
  {
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
  };

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  /* I have no idea where, but something is disabling blending before I draw. */
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glPushMatrix();

  glTranslatef(x, y, 0.0f);
  glScalef(w, h, 0.0f);

  glColor4f(r, g, b, 1.0f);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glPopMatrix();

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}
