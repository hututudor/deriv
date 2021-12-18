#include "ast_scene.h"

#include <algorithm>

#include "../utils/colors.h"
#include "../utils/screen.h"
#include "sidebar.h"

typedef struct {
  SDL_Texture* render_texture;
} ast_scene_state_t;

void set_renderer_color(SDL_Renderer* renderer, color_t color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void init_ast_scene(context_t* context) {
  context->scene_state =
      (ast_scene_state_t*)calloc(1, sizeof(ast_scene_state_t));

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  state->render_texture =
      SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, 1920, 1080);

  add_sidebar(context);
}

void render_ast_scene(context_t* context) {
  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  context->offset.x = std::max(0, std::min(1920, context->offset.x));
  context->offset.y = std::max(0, std::min(1080, context->offset.y));

  SDL_SetRenderTarget(context->renderer, state->render_texture);

  set_renderer_color(context->renderer, COLOR_COOL_GREY_050);
  SDL_RenderClear(context->renderer);

  set_renderer_color(context->renderer, COLOR_RED_VIVID_500);
  SDL_RenderDrawLine(context->renderer, 4, 100, 100, 300);

  SDL_SetRenderTarget(context->renderer, NULL);

  SDL_Rect dest;
  dest.x = 300 + context->offset.x;
  dest.y = context->offset.y;
  dest.w = SCREEN_WIDTH - 300;
  dest.h = SCREEN_HEIGHT;

  SDL_RenderCopy(context->renderer, state->render_texture, NULL, &dest);
}

void destroy_ast_scene(context_t* context) {
  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  SDL_DestroyTexture(state->render_texture);
}