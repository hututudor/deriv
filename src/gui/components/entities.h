#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdint.h>

typedef struct {
  int x, y;
} vector_t;

typedef struct {
  uint8_t r, g, b, a;
} color_t;

#endif