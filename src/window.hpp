#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"
#include "config.hpp"
#include <stdexcept>

class Window
{
public:
  Window()
      : m_window(SDL_CreateWindow("One Cannon and Target",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN))
  {
    if (!m_window)
    {
      throw std::runtime_error("Unable to create window");
    }
  }
  ~Window() { SDL_DestroyWindow(m_window); }

public:
  SDL_Window *&getWindow() { return m_window; }

private:
  SDL_Window *m_window;
};
