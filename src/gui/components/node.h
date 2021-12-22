#ifndef NODE_H
#define NODE_H

#include <SDL2/SDL.h>

#include "entities.h"
#include "text.h"

typedef struct {
  color_t background;
  color_t border_color;
  vector_t center_pos;
  int radius;

  char* content;
  color_t text_color;
  int font_size;

} gui_node_t;

void add_node(void* context, gui_node_t node);
void add_node(void* context, const char* content, vector_t center_pos,
              color_t border_color, color_t background, int font_size);

void update_node(void* context, gui_node_t& node);
void render_node(void* context, gui_node_t& node);

#endif