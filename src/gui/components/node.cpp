#include "node.h"

#include "../../utils/utils.h"
#include "../arrays/node_array.h"
#include "../utils/context.h"
#include "circle.h"
#include "text.h"

void add_node(void* context, gui_node_t node) {
  context_t* ctx = (context_t*)context;

  circle_t circle;
  circle.background = node.background;
  circle.border_color = node.border_color;
  circle.center_pos = node.center_pos;
  circle.radius = node.radius;
  add_circle(context, circle);

  text_t text;
  text.color = node.text_color;
  text.pos = node.center_pos;
  text.h_center = true;
  text.v_center = true;
  text.wrap = node.radius * 2 - 10;

  text.font = TTF_OpenFont("res/Helvetica.ttf", node.font_size);
  if (!text.font) {
    throw_error("font not found");
  }

  text.content = (char*)malloc(strlen(node.content) + 1);
  strcpy(text.content, node.content);
  add_text(context, text);

  push_node_array(ctx->node_array, node);
}

void add_node(void* context, const char* content, vector_t center_pos,
              int radius, color_t background, color_t border_color,
              color_t text_color, int font_size) {
  gui_node_t node;

  node.border_color = border_color;
  node.background = background;
  node.center_pos = center_pos;
  node.radius = radius;
  node.font_size = font_size;
  node.text_color = text_color;

  node.content = (char*)malloc(strlen(content) + 1);
  strcpy(node.content, content);

  add_node(context, node);
}

void render_node(void* context, gui_node_t& node) {}
void update_node(void* context, gui_node_t& node) {}