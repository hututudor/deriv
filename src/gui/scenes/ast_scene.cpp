#include "ast_scene.h"

#include <algorithm>
#include <cstdio>
#include <queue>

#include "../../ast/ast.h"
#include "../ast/ast_gui_utils.h"
#include "../components/circle.h"
#include "../utils/colors.h"
#include "../utils/screen.h"
#include "sidebar.h"

extern node_t* ast;

int startingColumn = -1;
int textureWidth = -1;
int textureHeight = -1;

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

  int columns = ComputeTreeColumns(ast, startingColumn);
  printf("columns:%d\n", columns);
  int rows = ComputeTreeRows(ast);
  printf("rows:%d\n", rows);

  textureWidth = columns * DEFAULT_RADIUS;
  textureHeight = rows * DEFAULT_RADIUS;

  state->render_texture =
      SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, 1920, 1080);

  add_sidebar(context);
}

void update_ast_scene(context_t* context) { update_sidebar(context); }

void render_ast_scene(context_t* context) {
  render_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  context->offset.x =
      std::max(0, std::min(1920 - SCREEN_WIDTH + 300, context->offset.x));
  context->offset.y = std::max(0, std::min(1080, context->offset.y));

  SDL_SetRenderTarget(context->renderer, state->render_texture);

  // SDL_RenderDrawLine(context->renderer, 4, 100, 100, 300);

  SDL_SetRenderTarget(context->renderer, NULL);

  SDL_Rect dest;
  dest.x = 300;
  dest.y = 0;
  dest.w = SCREEN_WIDTH - 300;
  dest.h = SCREEN_HEIGHT;

  SDL_Rect src;
  src.x = context->offset.x;
  src.y = context->offset.y;
  src.w = SCREEN_WIDTH - 300 - 400;
  src.h = SCREEN_HEIGHT - 400;

  SDL_RenderCopy(context->renderer, state->render_texture, &src, &dest);
}

void destroy_ast_scene(context_t* context) {
  destroy_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  SDL_DestroyTexture(state->render_texture);
}
