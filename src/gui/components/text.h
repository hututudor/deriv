#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL_ttf.h>

#include "entities.h"

typedef struct {
  char* content;
  color_t color;
  vector_t pos;
  bool h_center;
  bool v_center;
  int wrap;
  TTF_Font* font;

  int computed_width;
  int computed_height;
} text_t;

void add_text(void* context, text_t text);
void add_text(void* context, const char* content, vector_t pos, color_t color,
              bool h_center, bool v_center, int size, int wrap);

void render_text(void* context, text_t& text);

#endif