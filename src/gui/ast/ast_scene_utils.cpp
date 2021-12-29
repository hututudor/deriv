#include "ast_scene_utils.h"

#include <algorithm>

#include "../utils/colors.h"
#include "../utils/screen.h"
#include "ast_gui_utils.h"

void set_renderer_color(SDL_Renderer* renderer, color_t color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Add_Tree_Nodes(context_t* context, node_t* ast) {
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
