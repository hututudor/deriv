#include <SDL2/SDL.h>

#include "context.h"
#include "event.h"

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