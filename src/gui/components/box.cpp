#include "box.h"

#include <SDL2/SDL.h>

#include "../arrays/box_array.h"
#include "../utils/context.h"

void add_box(void* context, box_t box) {
  context_t* ctx = (context_t*)context;

  push_box_array(ctx->box_array, box);
}

void add_box(void* context, vector_t pos, vector_t size, color_t color) {
  box_t box;

  box.pos.x = pos.x;
  box.pos.y = pos.y;
  box.size.x = size.x;
  box.size.y = size.y;
  box.color = color;

  return add_box(context, box);
}

void render_box(void* context, box_t box) {
  context_t* ctx = (context_t*)context;

  SDL_SetRenderDrawColor(ctx->renderer, box.color.r, box.color.g, box.color.b,
                         box.color.a);

  SDL_Rect rect;
  rect.x = box.pos.x;
  rect.y = box.pos.y;
  rect.w = box.size.x;
  rect.h = box.size.y;

  SDL_RenderFillRect(ctx->renderer, &rect);
}