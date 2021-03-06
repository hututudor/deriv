#ifndef AST_SCENE_H
#define AST_SCENE_H

#include "../utils/context.h"

void init_ast_scene(context_t* context);
void update_ast_scene(context_t* context);
void render_ast_scene(context_t* context);
void destroy_ast_scene(context_t* context);

#endif