#include "text.h"

#include <SDL2/SDL.h>

#include <cstring>

#include "../../utils/utils.h"
#include "../arrays/text_array.h"
#include "../utils/context.h"

void add_text(void* context, text_t text) {
  context_t* ctx = (context_t*)context;

  push_text_array(ctx->text_array, text);
}

void add_text(void* context, const char* content, vector_t pos, color_t color,
              bool h_center, bool v_center, int size, int wrap) {
  text_t text;

  text.color = color;
  text.pos = pos;
  text.h_center = h_center;
  text.v_center = v_center;
  text.wrap = wrap;
  text.font = TTF_OpenFont("res/Helvetica.ttf", size);

  if (!text.font) {
    throw_error("font not found");
  }

  text.content = (char*)malloc(strlen(content) + 1);

  strcpy(text.content, content);

  add_text(context, text);
}

void render_text(void* context, text_t& text) {
  if (!strlen(text.content)) {
    text.computed_width = 0;
    text.computed_height = 0;
    return;
  }

  context_t* ctx = (context_t*)context;

  SDL_Surface* surface;
  SDL_Color color = {text.color.r, text.color.g, text.color.b, text.color.a};

  if (text.wrap) {
    surface = TTF_RenderText_Blended_Wrapped(text.font, text.content, color,
                                             text.wrap);
  } else {
    surface = TTF_RenderText_Blended(text.font, text.content, color);
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);

  text.computed_width = surface->w;
  text.computed_height = surface->h;

  SDL_FreeSurface(surface);

  SDL_Rect rect;
  rect.x = text.pos.x;
  rect.y = text.pos.y;
  rect.w = text.computed_width;
  rect.h = text.computed_height;

  if (text.h_center) {
    rect.x -= rect.w / 2;
  }

  if (text.v_center) {
    rect.y -= rect.h / 2;
  }

  SDL_RenderCopy(ctx->renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}