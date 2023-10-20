#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_video.h"
#include "config.hpp"
#include "projectile.hpp"
#include "state.hpp"
#include "text.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

class Renderer
{
public:
  Renderer(SDL_Window *window)
      : m_renderer(SDL_CreateRenderer(window, -1, 0)),
        m_cannonball_texture(IMG_LoadTexture(m_renderer, "assets/cannonball.jpg"))
  {
    if (!m_cannonball_texture)
    {
      throw std::runtime_error("Could not load image: " +
                               static_cast<std::string>(IMG_GetError()));
    }
  }
  ~Renderer() { SDL_DestroyRenderer(m_renderer); }

public:
  void render(const State &state)
  {
    SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(0),
                           static_cast<Uint8>(0),
                           static_cast<Uint8>(0), 255);
    SDL_RenderClear(m_renderer);

    for (const Projectile &ball : state.cannonballs)
    {
      SDL_Rect projectile_rect{static_cast<int>(ball.position.x),
                               static_cast<int>(ball.position.y),
                               PROJECTILE_SIZE, PROJECTILE_SIZE};
      SDL_RenderCopy(m_renderer, m_cannonball_texture, nullptr, &projectile_rect);
    }

    int fps = 1 / state.delta_time;

    Text fpsText(m_renderer, ("FPS: " + std::to_string(fps)).c_str(), 0, 0,
                 0.2f);
    fpsText.render(m_renderer);

    Text cannonball_text(
        m_renderer,
        ("CANNON BALLS: " + std::to_string(state.cannonballs.size())).c_str(),
        0, 60, 0.2f);
    cannonball_text.render(m_renderer);

    SDL_RenderPresent(m_renderer);
  }

private:
  SDL_Renderer *m_renderer;
  SDL_Texture *m_cannonball_texture;
};
