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

typedef struct {
  SDL_Texture* render_texture;

  int textureWidth = 1920;
  int textureHeight = 1080;

} ast_scene_state_t;

void set_renderer_color(SDL_Renderer* renderer, color_t color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Render_Tree_Nodes(context_t* context) {
  int columnCounter = 0;
  int rowCounter = 0;

  GetTreeSize(ast, columnCounter, rowCounter);
  location_array_t* array =
      Get_GuiNode_Locations(ast, columnCounter, rowCounter);

  int textureWidth = columnCounter * DEFAULT_RADIUS * 2 + 1;
  int textureHeight = rowCounter * DEFAULT_RADIUS * 2 + 1;

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;
  state->textureHeight = textureHeight;
  state->textureWidth = textureWidth;

  state->render_texture =
      SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);

  int radius = std::min(DEFAULT_RADIUS, std::min(textureWidth / columnCounter,
                                                 textureHeight / rowCounter));

  while (array->size) {
    node_location_t toRenderNode = pop_location_array(array);
    add_node(context, convert_token(toRenderNode.node->token),
             {toRenderNode.current->column * radius * 2 + radius,
              toRenderNode.current->row * radius * 2 + radius},
             DEFAULT_RADIUS, COLOR_BLUE_VIVID_900, COLOR_RED_VIVID_200,
             COLOR_BLUE_VIVID_900, 32);
  }

  destory_location_array(array);
}

void init_ast_scene(context_t* context) {
  context->scene_state =
      (ast_scene_state_t*)calloc(1, sizeof(ast_scene_state_t));
  add_sidebar(context);

  if (!ast) {
    add_text(context, "No input function", {332, 32}, COLOR_COOL_GREY_900,
             false, false, 16, 0);
    return;
  }

  Render_Tree_Nodes(context);
}

void update_ast_scene(context_t* context) { update_sidebar(context); }

void render_ast_scene(context_t* context) {
  render_sidebar(context);

  if (!ast) {
    return;
  }

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  context->offset.x = std::max(
      0, std::min(state->textureWidth - SCREEN_WIDTH + 300, context->offset.x));
  context->offset.y = std::max(
      0, std::min(state->textureHeight - SCREEN_HEIGHT, context->offset.y));

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
  dest.w = std::min(SCREEN_WIDTH - 300, state->textureWidth);
  dest.h = std::min(SCREEN_HEIGHT, state->textureHeight);

  SDL_Rect src;
  src.x = context->offset.x;
  src.y = context->offset.y;
  src.w = std::min(SCREEN_WIDTH - 300, state->textureWidth);
  src.h = std::min(SCREEN_HEIGHT, state->textureHeight);

  SDL_RenderCopy(context->renderer, state->render_texture, &src, &dest);
}

void destroy_ast_scene(context_t* context) {
  destroy_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  SDL_DestroyTexture(state->render_texture);
}
