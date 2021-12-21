#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

#include "entities.h"
#include "text.h"

typedef struct {
  char* content;
  color_t background;
  color_t color;
  vector_t pos;
  vector_t size;
  int font_size;
  void (*callback)(void* context);

  bool is_focused;
  uint32_t prev_pressed;
  text_t* text;
} input_t;

void add_input(void* context, input_t input);
void add_input(void* context, vector_t pos, vector_t size, color_t color,
               color_t background, int font_size);

void update_input(void* context, input_t& input);
void render_input(void* context, input_t& input);

void global_handle_key_press_event(void* context, SDL_Keysym sym);
void global_handle_text_input_event(void* context, SDL_TextInputEvent ev);

#endif