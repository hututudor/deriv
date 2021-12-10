#include "scene.h"

void change_scene(context_t* context, scene_type type) {
  context->current_scene = type;
}

void default_init_scene_fun(context_t* context) {}
void default_update_scene_fun(context_t* context) {}
void default_render_scene_fun(context_t* context) {}
void default_destroy_scene_fun(context_t* context) {}

scene_t* create_scene() {
  scene_t* scene = (scene_t*)malloc(sizeof(scene_t));

  scene->init = default_init_scene_fun;
  scene->update = default_update_scene_fun;
  scene->render = default_render_scene_fun;
  scene->destroy = default_destroy_scene_fun;

  return scene;
}

void destroy_scene(scene_t* scene) { free(scene); }

void init_current_scene(context_t* context, scene_t* scene) {
  scene->init(context);
}

void update_current_scene(context_t* context, scene_t* scene) {
  scene->update(context);
}

void render_current_scene(context_t* context, scene_t* scene) {
  scene->render(context);
}

void destroy_current_scene(context_t* context, scene_t* scene) {
  scene->destroy(context);
}