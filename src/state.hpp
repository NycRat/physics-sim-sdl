#pragma once

#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_stdinc.h"
#include "projectile.hpp"
#include <unordered_set>
#include <vector>

struct State
{
  bool should_quit = false;
  Uint64 last_tick = 0;
  float delta_time = 0.f;
  std::unordered_set<SDL_Keycode> pressed_keys;
  std::vector<Projectile> cannonballs;
};
