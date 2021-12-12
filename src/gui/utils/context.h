#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../arrays/box_array.h"
#include "../arrays/button_array.h"
#include "../arrays/text_array.h"
#include "./scene_types.h"

typedef struct {
  box_array_t* box_array;
  text_array_t* text_array;
  button_array_t* button_array;

  void* scene_state;
  scene_type current_scene;

  SDL_Renderer* renderer;
  TTF_Font* font;
} context_t;

#endif