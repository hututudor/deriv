#ifndef BUTTON_H
#define BUTTON_H

#include "entities.h"

typedef struct {
  char* label;
  color_t background;
  color_t color;
  vector_t pos;
  vector_t size;
  int font_size;
  void (*callback)(void* context);
} button_t;

void add_button(void* context, button_t button);
void add_button(void* context, const char* label, vector_t pos, vector_t size,
                color_t color, color_t background, int font_size,
                void (*callback)(void* context));

void update_button(void* context, button_t button);

#endif