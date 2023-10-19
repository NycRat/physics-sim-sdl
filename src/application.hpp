#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_ttf.h"
#include "config.hpp"
#include "events.hpp"
#include "projectile.hpp"
#include "renderer.hpp"
#include "state.hpp"
#include "text.hpp"
#include "window.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

inline float getDeltaTimeInSeconds(const Uint64 &start, const Uint64 &end)
{
  if (start > end)
  {
    throw std::runtime_error("Time going backwards");
  }
  return static_cast<float>(end - start) / SDL_GetPerformanceFrequency();
}

class Application
{
public:
  Application()
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
      throw std::runtime_error("Could not initialize SDL: " +
                               static_cast<std::string>(SDL_GetError()));
    }
    if (!IMG_Init(IMG_INIT_JPG))
    {
      throw std::runtime_error("Could not initialize SDL_image: " +
                               static_cast<std::string>(IMG_GetError()));
    }
    if (TTF_Init() < 0)
    {
      throw std::runtime_error("Could not initialize SDL_ttf: " +
                               static_cast<std::string>(TTF_GetError()));
    }
    Text::loadFont("assets/great_font.ttf");
  }
  ~Application()
  {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
  }

public:
  void run()
  {
    Window window;
    Renderer renderer(window.getWindow());
    Events events;
    State state;

    state.last_tick = SDL_GetPerformanceCounter();

    while (true)
    {
      Uint64 start = SDL_GetPerformanceCounter();

      events.handleEvents(state);
      if (state.should_quit)
      {
        break;
      }

      update(state);
      renderer.render(state);

      Uint64 end = SDL_GetPerformanceCounter();

      float updateTimeInMS = getDeltaTimeInSeconds(start, end) * 1000.f;
      state.delta_time = getDeltaTimeInSeconds(state.last_tick, end);
      state.last_tick = SDL_GetPerformanceCounter();

      SDL_Delay(std::max((1000.f / FPS_CAP) - updateTimeInMS, 0.f));
    }
  }

private:
  void update(State &state)
  {
    handleInput(state);

    for (int i = 0; i < state.cannonballs.size(); i += 1)
    {
      auto &ball = state.cannonballs[i];
      ball.update(state.delta_time);

      if (ball.position.x >= state.target.position.x)
      {
        state.cannonballs.erase(state.cannonballs.begin() + i);
        i--;
      }
    }

    state.target.update(state.delta_time);

    if (state.target.position.y + TARGET_SIZE >= WINDOW_HEIGHT)
    {
      state.target.position.y = WINDOW_HEIGHT - TARGET_SIZE;
      state.target.velocity.y = 0;
    }
  }

  void handleInput(State &state)
  {
    // static std::mt19937 mt(time(0));

    if (state.pressed_keys.count(SDLK_SPACE))
    {
      if (state.cannonballs.size() == 0)
      {
        Projectile target = {{TARGET_INITIAL_X, 0}, {0, 0}};
        state.target = target;
      }

      float start = WINDOW_HEIGHT * 4 / 5;
      float direction = atan2(start, TARGET_INITIAL_X);

      for (float velocity = 170; velocity <= 450; velocity += 50)
      {
        float uX = cos(direction) * velocity * CANNONBALL_SPEED;
        float uY = -sin(direction) * velocity * CANNONBALL_SPEED;
        state.cannonballs.push_back({{0, start}, {uX, uY}});
      }
    }
    if (state.pressed_keys.count(SDLK_r))
    {
      state.cannonballs.clear();
      state.target = {{0, 0}, {0, 0}};
    }
  }
};
