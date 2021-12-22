#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../arrays/box_array.h"
#include "../arrays/button_array.h"
#include "../arrays/circle_array.h"
#include "../arrays/input_array.h"
#include "../arrays/node_array.h"
#include "../arrays/text_array.h"
#include "./scene_types.h"

typedef struct {
  box_array_t* box_array;
  circle_array_t* circle_array;
  node_array_t* node_array;
  text_array_t* text_array;
  button_array_t* button_array;
  input_array_t* input_array;

  void* scene_state;
  scene_type current_scene;
  bool want_to_exit;

  vector_t offset;

  SDL_Renderer* renderer;
} context_t;

#endif