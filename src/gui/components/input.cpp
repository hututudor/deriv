#include "input.h"

#include <SDL2/SDL.h>

#include <cstring>

#include "../arrays/input_array.h"
#include "../utils/context.h"
#include "box.h"
#include "text.h"

void add_input(void* context, input_t input) {
  context_t* ctx = (context_t*)context;

  box_t box;
  box.color = input.background;
  box.pos = input.pos;
  box.size = input.size;

  text_t text = {0};
  text.color = input.color;
  text.pos.x = input.pos.x + 16;
  text.pos.y = input.pos.y + input.size.y / 2;

  // TODO(tudor): refactor this
  text.font = TTF_OpenFont("res/Helvetica.ttf", input.font_size);
  text.wrap = 0;
  text.v_center = true;
  text.h_center = false;
  text.content = (char*)malloc(10000);

  add_box(context, box);
  add_text(context, text);

  input.text = &ctx->text_array->texts[ctx->text_array->size - 1];

  push_input_array(ctx->input_array, input);
}

void add_input(void* context, vector_t pos, vector_t size, color_t color,
               color_t background, int font_size) {
  input_t input;

  input.color = color;
  input.background = background;
  input.pos = pos;
  input.size = size;
  input.font_size = font_size;
  input.prev_pressed = 0;
  input.is_focused = 0;
  input.callback = nullptr;

  add_input(context, input);
}

void update_input(void* context, input_t& input) {
  context_t* ctx = (context_t*)context;
  int x, y;

  uint32_t buttons = SDL_GetMouseState(&x, &y);

  if ((buttons & SDL_BUTTON_LMASK) & !(input.prev_pressed & SDL_BUTTON_LMASK)) {
    if (x >= input.pos.x && x <= input.pos.x + input.size.x &&
        y >= input.pos.y && y <= input.pos.y + input.size.y) {
      for (int i = 0; i < ctx->input_array->size; i++) {
        ctx->input_array->inputs[i].is_focused = false;
      }

      input.is_focused = true;
    }
  }

  input.prev_pressed = buttons;

  strcpy(input.text->content, input.content);
}

void render_input(void* context, input_t& input) {
  if (input.is_focused) {
    SDL_SetRenderDrawColor(((context_t*)context)->renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(((context_t*)context)->renderer,
                       input.pos.x + input.text->computed_width + 16,
                       input.pos.y + input.size.y / 4,
                       input.pos.x + input.text->computed_width + 16,
                       input.pos.y + input.size.y - input.size.y / 4);
  }
}

void global_handle_key_press_event(void* context, SDL_Keysym sym) {
  context_t* ctx = (context_t*)context;

  input_t* focused_input = nullptr;
  int focused_index = 0;

  for (int i = 0; i < ctx->input_array->size; i++) {
    if (ctx->input_array->inputs[i].is_focused) {
      focused_input = &ctx->input_array->inputs[i];
      focused_index = i;
      break;
    }
  }

  if (!focused_input) {
    return;
  }

  bool is_ctrl_pressed = SDL_GetModState() & KMOD_CTRL;
  bool is_shift_pressed = SDL_GetModState() & KMOD_SHIFT;

  switch (sym.sym) {
    case SDLK_BACKSPACE:
      if (is_ctrl_pressed) {
        strcpy(focused_input->content, "");
      } else {
        int len = strlen(focused_input->content);
        focused_input->content[len - 1] = 0;
      }
      break;

    case SDLK_c:
      if (is_ctrl_pressed) {
        SDL_SetClipboardText(focused_input->content);
      }
      break;

    case SDLK_x:
      if (is_ctrl_pressed) {
        SDL_SetClipboardText(focused_input->content);
        strcpy(focused_input->content, "");
      }
      break;

    case SDLK_v:
      if (is_ctrl_pressed) {
        strcpy(focused_input->content, SDL_GetClipboardText());
      }
      break;

    case SDLK_TAB:
      focused_index += is_shift_pressed ? -1 : 1;

      for (int i = 0; i < ctx->input_array->size; i++) {
        ctx->input_array->inputs[i].is_focused = false;
      }

      if (focused_index < 0) {
        focused_index = ctx->input_array->size - 1;
      }

      focused_index %= ctx->input_array->size;
      ctx->input_array->inputs[focused_index].is_focused = true;

      break;

    case SDLK_RETURN:
      if (focused_input->callback) {
        focused_input->callback(context);
      }
      break;
  }
}

void global_handle_text_input_event(void* context, SDL_TextInputEvent ev) {
  context_t* ctx = (context_t*)context;

  input_t* focused_input = nullptr;

  for (int i = 0; i < ctx->input_array->size; i++) {
    if (ctx->input_array->inputs[i].is_focused) {
      focused_input = &ctx->input_array->inputs[i];
      break;
    }
  }

  if (!focused_input) {
    return;
  }

  strcat(focused_input->content, ev.text);
}