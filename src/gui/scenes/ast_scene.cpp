#include "ast_scene.h"

#include <algorithm>
#include <cstdio>
#include <queue>

#include "../../ast/ast.h"
#include "../ast/ast_gui_utils.h"
#include "../components/circle.h"
#include "../components/node.h"
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

void DFS(context_t* context, node_t* node, int line, int col) {
  if (!node) {
    return;
  }

  printf("node %s at %d, %d with %d, %d -> %d\n", convert_token(node->token),
         col * DEFAULT_RADIUS * 2 + DEFAULT_RADIUS,
         line * DEFAULT_RADIUS * 2 + DEFAULT_RADIUS, line, col, startingColumn);

  add_node(context, convert_token(node->token),
           {col * DEFAULT_RADIUS * 2 + DEFAULT_RADIUS,
            line * DEFAULT_RADIUS * 2 + DEFAULT_RADIUS},
           DEFAULT_RADIUS, COLOR_BLUE_VIVID_900, COLOR_COOL_GREY_050,
           COLOR_BLUE_VIVID_900, 32);

  DFS(context, node->left, line + 1, col - 1);
  DFS(context, node->right, line + 1, col + 1);
}

void init_ast_scene(context_t* context) {
  context->scene_state =
      (ast_scene_state_t*)calloc(1, sizeof(ast_scene_state_t));

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  add_sidebar(context);

  if (!ast) {
    add_text(context, "No input function", {332, 32}, COLOR_COOL_GREY_900,
             false, false, 16, 0);
    return;
  }

  int columns = ComputeTreeColumns(ast, startingColumn);
  int rows = ComputeTreeRows(ast);
  textureWidth = columns * DEFAULT_RADIUS * 2;
  textureHeight = rows * DEFAULT_RADIUS * 2;

  printf("cols: %d, rows: %d", columns, rows);

  printf("width: %d \n height: %d \n", textureWidth, textureHeight);

  state->render_texture = SDL_CreateTexture(
      context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
      std::min(SCREEN_WIDTH + 300, textureWidth),
      std::min(SCREEN_HEIGHT, textureHeight));

  DFS(context, ast, 0, startingColumn - 1);
}

void update_ast_scene(context_t* context) { update_sidebar(context); }

void render_ast_scene(context_t* context) {
  render_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  context->offset.x = std::max(
      0, std::min(textureWidth - SCREEN_WIDTH + 300, context->offset.x));
  context->offset.y = std::max(0, std::min(textureHeight, context->offset.y));

  SDL_SetRenderTarget(context->renderer, state->render_texture);

  set_renderer_color(context->renderer, COLOR_COOL_GREY_050);
  SDL_RenderClear(context->renderer);
  // SDL_RenderDrawLine(context->renderer, 4, 100, 100, 300);

  render_circle_array(context, context->circle_array);
  render_text_array(context, context->node_text_array);
  render_node_array(context, context->node_array);

  SDL_SetRenderTarget(context->renderer, NULL);

  SDL_Rect dest;
  dest.x = 300;
  dest.y = 0;
  dest.w = textureWidth;
  dest.h = textureHeight;

  SDL_Rect src;
  src.x = context->offset.x;
  src.y = context->offset.y;
  src.w = SCREEN_WIDTH - 300;
  src.h = SCREEN_HEIGHT;

  SDL_RenderCopy(context->renderer, state->render_texture, &src, &dest);
}

void destroy_ast_scene(context_t* context) {
  destroy_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  SDL_DestroyTexture(state->render_texture);
}
