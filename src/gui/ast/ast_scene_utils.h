#ifndef AST_SCENE_UTILS
#define AST_SCENE_UTILS

#include "../../ast/ast.h"
#include "../components/entities.h"
#include "../components/text.h"
#include "../utils/context.h"
#include "SDL2/SDL.h"

typedef struct {
  SDL_Texture* render_texture;
  text_t* no_function_text;

  int textureWidth;
  int textureHeight;
} ast_scene_state_t;

void set_renderer_color(SDL_Renderer* renderer, color_t color);

void Add_Tree_Nodes(context_t* context, node_t* ast);

#endif