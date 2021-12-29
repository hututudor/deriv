#include <algorithm>
#include <cstdio>
#include <queue>

#include "../../ast/ast.h"
#include "../ast/ast_gui_utils.h"
#include "../ast/ast_scene_utils.h"
#include "../components/circle.h"
#include "../components/line.h"
#include "../components/node.h"
#include "../i18n/i18n.h"
#include "../utils/colors.h"
#include "../utils/screen.h"
#include "ast_scene.h"
#include "sidebar.h"

extern node_t* ast_der;

void init_deriv_ast_scene(context_t* context) {
  add_sidebar(context);

  context->scene_state =
      (ast_scene_state_t*)calloc(1, sizeof(ast_scene_state_t));
  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  state->no_function_text = nullptr;

  if (!ast_der) {
    add_text(context, get_i18n_string(TRANSLATION_NO_INPUT_FUNCTION), {332, 32},
             COLOR_COOL_GREY_900, false, false, 16, 0);

    state->no_function_text =
        &context->text_array->texts[context->text_array->size - 1];

    return;
  }

  Add_Tree_Nodes(context, ast_der);
}

void update_deriv_ast_scene(context_t* context) { update_sidebar(context); }

void render_deriv_ast_scene(context_t* context) {
  render_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  if (!ast_der) {
    strcpy(state->no_function_text->content,
           get_i18n_string(TRANSLATION_NO_INPUT_FUNCTION));

    return;
  }

  context->offset.x = std::max(
      0, std::min(state->textureWidth - SCREEN_WIDTH + 300, context->offset.x));
  context->offset.y = std::max(
      0, std::min(state->textureHeight - SCREEN_HEIGHT, context->offset.y));

  SDL_SetRenderTarget(context->renderer, state->render_texture);

  set_renderer_color(context->renderer, COLOR_COOL_GREY_050);
  SDL_RenderClear(context->renderer);

  render_line_array(context, context->line_array);
  render_circle_array(context, context->circle_array);
  render_text_array(context, context->node_text_array);
  render_node_array(context, context->node_array);

  SDL_SetRenderTarget(context->renderer, nullptr);

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

void destroy_deriv_ast_scene(context_t* context) {
  destroy_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  SDL_DestroyTexture(state->render_texture);
}
