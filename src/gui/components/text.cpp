#include "text.h"

#include <SDL2/SDL.h>

#include "../arrays/text_array.h"
#include "../utils/context.h"

void add_text(void* context, text_t text) {
  context_t* ctx = (context_t*)context;

  push_text_array(ctx->text_array, text);
}

void add_text(void* context, const char* content, vector_t pos, color_t color,
              bool h_center, bool v_center) {
  text_t text;

  text.color = color;
  text.pos = pos;
  text.h_center = h_center;
  text.v_center = v_center;
  text.content = (char*)malloc(strlen(content) + 1);

  strcpy(text.content, content);

  add_text(context, text);
}

void render_text(void* context, text_t text) {
  context_t* ctx = (context_t*)context;

  int text_width;
  int text_height;

  SDL_Surface* surface;
  SDL_Color color = {text.color.r, text.color.g, text.color.b, text.color.a};

  surface = TTF_RenderText_Blended(ctx->font, text.content, color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);

  text_width = surface->w;
  text_height = surface->h;

  SDL_FreeSurface(surface);

  SDL_Rect rect;
  rect.x = text.pos.x;
  rect.y = text.pos.y;
  rect.w = text_width;
  rect.h = text_height;

  if (text.h_center) {
    rect.x -= rect.w / 2;
  }

  if (text.v_center) {
    rect.y -= rect.h / 2;
  }

  SDL_RenderCopy(ctx->renderer, texture, NULL, &rect);
  SDL_DestroyTexture(texture);
}