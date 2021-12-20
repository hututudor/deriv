#ifndef INPUT_SCENE_H
#define INPUT_SCENE_H

#include "../utils/context.h"

void init_input_scene(context_t* context);
void update_input_scene(context_t* context);
void render_input_scene(context_t* context);
void destroy_input_scene(context_t* context);

#endif