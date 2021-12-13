#ifndef SCENE_H
#define SCENE_H

#include "./context.h"

typedef struct {
  void (*init)(context_t* context);
  void (*update)(context_t* context);
  void (*render)(context_t* context);
  void (*destroy)(context_t* context);
} scene_t;

void change_scene(context_t* context, scene_type type);

scene_t* create_scene();
void destroy_scene(scene_t* scene);

void init_current_scene(context_t* context, scene_t* scene);
void update_current_scene(context_t* context, scene_t* scene);
void render_current_scene(context_t* context, scene_t* scene);
void destroy_current_scene(context_t* context, scene_t* scene);

#endif