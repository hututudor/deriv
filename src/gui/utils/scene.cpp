#include "scene.h"

#include "../arrays/box_array.h"
#include "../arrays/button_array.h"
#include "../arrays/input_array.h"
#include "../arrays/text_array.h"

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
  context->box_array = init_box_array();
  context->text_array = init_text_array();
  context->button_array = init_button_array();
  context->input_array = init_input_array();

  context->offset = {0};

  scene->init(context);
}

void update_current_scene(context_t* context, scene_t* scene) {
  update_button_array(context, context->button_array);
  update_input_array(context, context->input_array);

  scene->update(context);
}

void render_current_scene(context_t* context, scene_t* scene) {
  render_box_array(context, context->box_array);
  render_text_array(context, context->text_array);
  render_input_array(context, context->input_array);

  scene->render(context);
}

void destroy_current_scene(context_t* context, scene_t* scene) {
  destory_box_array(context->box_array);
  destory_text_array(context->text_array);
  destory_button_array(context->button_array);
  destory_input_array(context->input_array);

  scene->destroy(context);

  if (context->scene_state) {
    free(context->scene_state);
    context->scene_state = nullptr;
  }

  if (context->extra_state) {
    free(context->extra_state);
    context->extra_state = nullptr;
  }
}