#include <glview/glview.h>
#include <bps/bps.h>
#include <bps/screen.h>

#include <ctime>
#include <cmath>
#include <cstdint>
#include <stdio.h>
#include <sstream>

#include "bbutil.h"

#include "game.hpp"
#include "globals.hpp"

struct App
{
  float dfps;
  uint64_t timeStart, oldTime;
  uint64_t fpsTimeStart;
  unsigned frames;

  font_t *mainFont;
};

static uint64_t GetTicks()
{
  timespec spec;

  clock_gettime(CLOCK_REALTIME, &spec);

  //return round(spec.tv_nsec / 1.0e6);
  return (uint64_t)(spec.tv_nsec / 1.0e6) + spec.tv_sec * 1000;
}

static void frame(void *data)
{
  App *app = (App*)data;

  /* Calculate delta time */
  app->timeStart = GetTicks();
  Globals::DeltaTime = (float)(app->timeStart - app->oldTime) / app->dfps;
  app->oldTime = app->timeStart;

  /* Update & draw game */
  Game::Update();
  Game::Draw();

  /* Calculate FPS */
  if(GetTicks() >= app->fpsTimeStart + 1000)
  {
    Globals::FPS = app->frames;
    app->frames = 0;
    app->fpsTimeStart = GetTicks();
  }
  /*else*/ ++app->frames;

  /* Print FPS */
  static std::stringstream ss;
  ss.str("");
  //ss << "FPS: " << Globals::FPS;
  ss << Globals::ScreenWidth << ", " << Globals::ScreenHeight;

  float textWidth, textHeight;
  bbutil_measure_text(app->mainFont, ss.str().c_str(), &textWidth, &textHeight);

  float x = -Globals::ScreenWidth * 0.5f;
  float y = Globals::ScreenHeight * 0.5f - textHeight;

  bbutil_render_text(app->mainFont, ss.str().c_str(), x, y, 1.0f, 1.0f, 1.0f, 1.0f);
}

static void init(void *data)
{
  App *app = (App*)data;

  /* Set screen size */
  unsigned int _width, _height;
  glview_get_size(&_width, &_height);
  Globals::ScreenWidth = (float)_width;
  Globals::ScreenHeight = (float)_height;

  /* Load font */
  app->mainFont = bbutil_load_font("./app/native/assets/arial.ttf", 16, 356);

  app->oldTime = GetTicks();

  Game::Init();
}

static void fina(void *data)
{
  App *app = (App*)data;

  Game::Fina();

  if(app->mainFont)
    bbutil_destroy_font(app->mainFont);
}

static void resize(unsigned int width, unsigned int height, void*)
{
  Globals::ScreenWidth = (float)width;
  Globals::ScreenHeight = (float)height;
}

static void event(bps_event_t *event, int domain, int code, void *data)
{
  if(domain == screen_get_domain())
  {
    screen_event_t screenEvent = screen_event_get_event(event);

    int eventType;
    screen_get_event_property_iv(screenEvent, SCREEN_PROPERTY_TYPE, &eventType);

    if(eventType == SCREEN_EVENT_MTOUCH_TOUCH/* || eventType == SCREEN_EVENT_MTOUCH_MOVE*/)
    {
      int pair[2];
      screen_get_event_property_iv(screenEvent, SCREEN_PROPERTY_SOURCE_POSITION, pair);

      Game::OnScreenTouch(pair[0], pair[1]);
    }
  }
}

int main(int argc, char **argv)
{
  glview_initialize(GLVIEW_API_OPENGLES_11, &frame);
  glview_register_initialize_callback(&init);
  glview_register_finalize_callback(&fina);
  glview_register_resize_callback(&resize);
  glview_register_event_callback(&event);

  App app;
  app.dfps = 1000.0f / 60.0f;
  app.fpsTimeStart = GetTicks();
  app.frames = 0;

  glview_set_callback_data(&app);

  return glview_loop();
}
