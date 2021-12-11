#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "gui/components/box.h"
#include "gui/components/text.h"
#include "gui/utils/scene.h"
#include "utils/utils.h"

#define SCENE_COUNT 10

void init_scene_1(context_t* context) {
  add_box(context, {100, 300}, {100, 150}, {0, 255, 0, 255});
}

void update_scene_1(context_t* context) { change_scene(context, SCENE_A); }

void callback_b1(void* context) { change_scene((context_t*)context, SCENE_B); }
void callback_b2(void* context) { change_scene((context_t*)context, SCENE_A); }

void init_scene_2(context_t* context) {
  add_box(context, {200, 300}, {100, 150}, {255, 255, 0, 255});
  add_box(context, {100, 300}, {100, 50}, {0, 255, 0, 255});

  add_text(context, "this is a nice text", {150, 325}, {255, 0, 0, 255}, true,
           true);

  add_button(context, "Switch to scene 2", {0, 0}, {200, 44},
             {255, 255, 255, 125}, {125, 0, 125, 255}, callback_b1);
}

void init_scene_3(context_t* context) {
  add_box(context, {200, 300}, {300, 150}, {0, 0, 255, 255});

  add_button(context, "Switch to scene 1", {0, 0}, {200, 44},
             {255, 255, 255, 125}, {125, 0, 125, 255}, callback_b2);
}

void render_scene_2(context_t* context) {
  SDL_SetRenderDrawColor(context->renderer, 255, 0, 255, 255);
  SDL_RenderDrawLine(context->renderer, 0, 0, 200, 200);

  context->text_array->texts[0].pos.x++;
}

scene_t** create_scenes() {
  scene_t** scenes = (scene_t**)calloc(sizeof(scene_t*), SCENE_COUNT);

  scenes[SCENE_INIT] = create_scene();
  scenes[SCENE_INIT]->init = init_scene_1;
  scenes[SCENE_INIT]->update = update_scene_1;

  scenes[SCENE_A] = create_scene();
  scenes[SCENE_A]->init = init_scene_2;
  scenes[SCENE_A]->render = render_scene_2;

  scenes[SCENE_B] = create_scene();
  scenes[SCENE_B]->init = init_scene_3;

  return scenes;
}

void destroy_scenes(scene_t** scenes) {
  for (int i = 0; i < SCENE_COUNT; i++) {
    if (scenes[i]) {
      destroy_scene(scenes[i]);
    }
  }

  free(scenes);
}

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

  SDL_Window* window =
      SDL_CreateWindow("Deriv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       640, 480, SDL_WINDOW_SHOWN);

  if (!window) {
    throw_error("could not create window");
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  TTF_Font* font = TTF_OpenFont("res/Helvetica.ttf", 16);

  if (!font) {
    throw_error("could not load font");
  }

  scene_t** scenes = create_scenes();

  context_t context;
  context.renderer = renderer;
  context.current_scene = SCENE_INIT;
  context.font = font;

  SDL_Event event;
  bool running = true;

  init_current_scene(&context, scenes[SCENE_INIT]);

  while (running) {
    SDL_PumpEvents();

    while (SDL_PollEvent(&event)) {
      running = event.type != SDL_QUIT;
    }

    if (!running) {
      destroy_current_scene(&context, scenes[context.current_scene]);
      break;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    scene_type current_scene_in_loop = context.current_scene;

    update_current_scene(&context, scenes[current_scene_in_loop]);
    render_current_scene(&context, scenes[current_scene_in_loop]);

    SDL_RenderPresent(renderer);

    if (context.current_scene != current_scene_in_loop) {
      destroy_current_scene(&context, scenes[current_scene_in_loop]);
      init_current_scene(&context, scenes[context.current_scene]);
    }
  }

  destroy_scenes(scenes);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();

  return 0;
}
