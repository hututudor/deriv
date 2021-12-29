#include "ast_scene.h"

#include <algorithm>
#include <cstdio>
#include <queue>

#include "../../ast/ast.h"
#include "../ast/ast_gui_utils.h"
#include "../components/circle.h"
#include "../components/line.h"
#include "../components/node.h"
#include "../i18n/i18n.h"
#include "../utils/colors.h"
#include "../utils/screen.h"
#include "sidebar.h"

extern node_t* ast;

typedef struct {
  SDL_Texture* render_texture;
  text_t* no_function_text;

  int textureWidth;
  int textureHeight;
} ast_scene_state_t;

void set_renderer_color(SDL_Renderer* renderer, color_t color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Add_Tree_Nodes(context_t* context) {
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

  for (int i = 0; i < array->size; i++) {
    vector_t parent = {
        array->locations[i].current->column * radius * 2 + radius,
        array->locations[i].current->row * radius * 2 + radius,
    };

    if (array->locations[i].left) {
      vector_t child = {
          array->locations[i].left->column * radius * 2 + radius,
          array->locations[i].left->row * radius * 2 + radius,
      };

      add_line(context, parent, child, COLOR_BLUE_VIVID_900);
    }

    if (array->locations[i].right) {
      vector_t child = {
          array->locations[i].right->column * radius * 2 + radius,
          array->locations[i].right->row * radius * 2 + radius,
      };

      add_line(context, parent, child, COLOR_BLUE_VIVID_900);
    }
  }

  while (array->size) {
    node_location_t toRenderNode = pop_location_array(array);

    if (toRenderNode.current->row == 0) {
      int x = toRenderNode.current->column * radius * 2 + radius;

      if (x > SCREEN_WIDTH - 300) {
        context->offset.x =
            std::min(textureWidth, x - (SCREEN_WIDTH - 300) / 2);
      }
    }

    add_node(context, convert_token(toRenderNode.node->token),
             {toRenderNode.current->column * radius * 2 + radius,
              toRenderNode.current->row * radius * 2 + radius},
             DEFAULT_RADIUS, COLOR_BLUE_VIVID_900, COLOR_BLUE_VIVID_100,
             COLOR_BLUE_VIVID_900, 32);
  }

  destory_location_array(array);
}

void init_ast_scene(context_t* context) {
  add_sidebar(context);

  context->scene_state =
      (ast_scene_state_t*)calloc(1, sizeof(ast_scene_state_t));
  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  state->no_function_text = nullptr;

  if (!ast) {
    add_text(context, get_i18n_string(TRANSLATION_NO_INPUT_FUNCTION), {332, 32},
             COLOR_COOL_GREY_900, false, false, 16, 0);

    state->no_function_text =
        &context->text_array->texts[context->text_array->size - 1];

    return;
  }

  Add_Tree_Nodes(context);
}

void update_ast_scene(context_t* context) { update_sidebar(context); }

void render_ast_scene(context_t* context) {
  render_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  if (!ast) {
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

void destroy_ast_scene(context_t* context) {
  destroy_sidebar(context);

  ast_scene_state_t* state = (ast_scene_state_t*)context->scene_state;

  SDL_DestroyTexture(state->render_texture);
}
