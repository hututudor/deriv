#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>

#include "../arrays/box_array.h"
#include "./scene_types.h"

typedef struct {
  box_array_t* box_array;
  scene_type current_scene;
  SDL_Renderer* renderer;
} context_t;

#endif