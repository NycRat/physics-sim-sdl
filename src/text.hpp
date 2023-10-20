#pragma once

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_ttf.h"
#include <stdexcept>

class Text
{
public:
  Text(SDL_Renderer *renderer, const char *text, int x, int y, float scale)
  {
    SDL_Color fg = {255, 255, 255};
    SDL_Color bg = {0, 0, 0};
    // SDL_Surface *surface = TTF_RenderText_Solid(m_font, text, color);
    SDL_Surface *surface = TTF_RenderText_Shaded(m_font, text, fg, bg);

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    messageRect = {x, y, static_cast<int>(surface->w * scale),
                   static_cast<int>(surface->h * scale)};

    SDL_FreeSurface(surface);
  }
  ~Text() { SDL_DestroyTexture(m_texture); }

public:
  void render(SDL_Renderer *renderer)
  {
    SDL_RenderCopy(renderer, m_texture, NULL, &messageRect);
  }
  static void loadFont(const char *file)
  {
    m_font = TTF_OpenFont(file, 256);
    if (!m_font)
    {
      throw std::runtime_error("Could not load font");
    }
  }

private:
  inline static TTF_Font *m_font;
  SDL_Texture *m_texture;
  SDL_Rect messageRect;
};
