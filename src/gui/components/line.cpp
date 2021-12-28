#include "line.h"

#include <SDL2/SDL.h>

#include <cstring>

#include "../arrays/line_array.h"
#include "../utils/context.h"
#include "box.h"
#include "text.h"

void add_line(void* context, line_t line) {
  context_t* ctx = (context_t*)context;

  push_line_array(ctx->line_array, line);
}

void add_line(void* context, vector_t parent, vector_t child, color_t color) {
  line_t line;

  line.parent = parent;
  line.child = child;
  line.color = color;

  add_line(context, line);
}

void render_line(void* context, line_t line) {
  SDL_SetRenderDrawColor(((context_t*)context)->renderer, line.color.r,
                         line.color.g, line.color.b, line.color.a);

  SDL_RenderDrawLine(((context_t*)context)->renderer, line.parent.x,
                     line.parent.y, line.child.x, line.child.y);
}
