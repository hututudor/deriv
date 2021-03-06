#include "events.h"

#include <SDL2/SDL.h>

#include "context.h"

void handle_key_press(void* context, SDL_Keysym sym) {
  context_t* ctx = (context_t*)context;

  int multiplicator = 30;

  switch (sym.sym) {
    case SDLK_a:
      ctx->offset.x -= multiplicator;
      break;
    case SDLK_d:
      ctx->offset.x += multiplicator;
      break;
    case SDLK_w:
      ctx->offset.y -= multiplicator;
      break;
    case SDLK_s:
      ctx->offset.y += multiplicator;
      break;
  }
}

void handle_mouse_move(void* context, SDL_MouseMotionEvent event) {
  context_t* ctx = (context_t*)context;

  if (event.state & SDL_BUTTON_LMASK) {
    ctx->offset.x -= event.xrel;
    ctx->offset.y -= event.yrel;
  }
}