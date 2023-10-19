#pragma once

#include "SDL2/SDL_rect.h"
#include "config.hpp"
#include <cmath>

struct Projectile
{
  SDL_FPoint position;
  SDL_FPoint velocity;
  void update(float deltaTime)
  {
    velocity.y += GRAVITY * deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
  }
};
