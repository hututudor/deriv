#include "button.h"

#include <SDL2/SDL.h>

#include <cstring>

#include "../arrays/button_array.h"
#include "../utils/context.h"
#include "box.h"
#include "text.h"

void add_button(void* context, button_t button) {
  context_t* ctx = (context_t*)context;

  push_button_array(ctx->button_array, button);

  box_t box;
  box.color = button.background;
  box.pos = button.pos;
  box.size = button.size;

  text_t text = {0};
  text.color = button.color;
  text.pos.x = button.pos.x + button.size.x / 2;
  text.pos.y = button.pos.y + button.size.y / 2;

  // TODO(tudor): refactor this
  text.font = TTF_OpenFont("res/Helvetica.ttf", button.font_size);
  text.v_center = true;
  text.h_center = true;
  text.content = (char*)malloc(strlen(button.label) + 1);

  strcpy(text.content, button.label);

  add_box(context, box);
  add_text(context, text);
}

void add_button(void* context, const char* label, vector_t pos, vector_t size,
                color_t color, color_t background, int font_size,
                void (*callback)(void* context)) {
  button_t button;

  button.color = color;
  button.background = background;
  button.pos = pos;
  button.size = size;
  button.font_size = font_size;
  button.prev_pressed = 0;
  button.callback = callback ? callback : nullptr;

  button.label = (char*)malloc(strlen(label) + 1);

  strcpy(button.label, label);

  add_button(context, button);
}

void update_button(void* context, button_t button) {
  int x, y;

  uint32_t buttons = SDL_GetMouseState(&x, &y);

  if (button.callback && (buttons & SDL_BUTTON_LMASK) &
                             !(button.prev_pressed & SDL_BUTTON_LMASK)) {
    if (x >= button.pos.x && x <= button.pos.x + button.size.x &&
        y >= button.pos.y && y <= button.pos.y + button.size.y) {
      button.callback(context);
    }
  }

  button.prev_pressed = buttons;
}