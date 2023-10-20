#pragma once

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "state.hpp"
#include <iostream>

class Events
{
public:
  void handleEvents(State &state)
  {
    while (SDL_PollEvent(&m_event))
    {
      switch (m_event.type)
      {
      case SDL_QUIT:
        state.should_quit = true;
        break;
      case SDL_KEYDOWN:
        state.pressed_keys.insert(m_event.key.keysym.sym);
        break;
      case SDL_KEYUP:
        state.pressed_keys.erase(m_event.key.keysym.sym);
        break;
      }
    }
  }

private:
  SDL_Event m_event;
};
