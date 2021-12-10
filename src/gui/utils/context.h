#ifndef CONTEXT_H
#define CONTEXT_H

#include "./scene_types.h"
#include "SDL2/SDL.h"

typedef struct {
  scene_type current_scene;
  SDL_Renderer* renderer;
} context_t;

#endif