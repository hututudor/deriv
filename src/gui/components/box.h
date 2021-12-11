#ifndef BOX_H
#define BOX_H

#include "entities.h"

typedef struct {
  color_t color;
  vector_t pos;
  vector_t size;
} box_t;

void add_box(void* context, box_t box);
void add_box(void* context, vector_t pos, vector_t size, color_t color);

void render_box(void* context, box_t box);

#endif