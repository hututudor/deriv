#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>

#include "entities.h"

typedef struct {
  vector_t parent;
  vector_t child;
  color_t color;
} line_t;

void add_line(void* context, line_t line);
void add_line(void* context, vector_t parent, vector_t child, color_t color);

void render_line(void* context, line_t line);

#endif