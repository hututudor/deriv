#include "ast_scene.h"

#include "../utils/colors.h"
#include "../utils/screen.h"
#include "sidebar.h"

void init_ast_scene(context_t* context) { add_sidebar(context); }

void render_ast_scene(context_t* context) {
  SDL_Texture* render_texture =
      SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, 1920, 1080);

  SDL_SetRenderTarget(context->renderer, render_texture);
  SDL_RenderClear(context->renderer);

  SDL_SetRenderDrawColor(context->renderer, 255, 0, 0, 255);
  SDL_RenderDrawLine(context->renderer, 4, 100, 100, 300);

  SDL_SetRenderTarget(context->renderer, NULL);

  static int x = 0;

  SDL_Rect dest;
  dest.x = 300 - x--;
  dest.y = -x;
  dest.w = SCREEN_WIDTH - 300;
  dest.h = SCREEN_HEIGHT;

  SDL_RenderCopy(context->renderer, render_texture, NULL, &dest);
  SDL_DestroyTexture(render_texture);
}