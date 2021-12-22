#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

#include "entities.h"

typedef struct {
  color_t border_color;
  color_t background;
  vector_t center_pos;

  int radius;
} circle_t;

#define DEFAULT_RADIUS 64

void add_circle(void* context, circle_t circle);
void add_circle(void* context, vector_t center_pos, int radius,
                color_t background, color_t border_color);

void render_circle(void* context, circle_t circle);

void SDL_RenderDrawCircle(SDL_Renderer* renderer, vector_t center_pos,
                          int radius, color_t border_color);

void SDL_RenderFillCircle(SDL_Renderer* renderer, vector_t center_pos,
                          int radius, color_t background);

#endif