#ifndef BUTTON_H
#define BUTTON_H

#include "entities.h"

typedef struct {
  char* label;
  color_t background;
  color_t color;
  vector_t pos;
  vector_t size;
} button_t;

#endif