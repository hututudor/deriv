#include <SDL2/SDL.h>

#include <iostream>

#include "gui/components/box.h"
#include "gui/utils/scene.h"

#define SCENE_COUNT 10

void init_scene_1(context_t* context) {
  add_box(context, {100, 300}, {100, 150}, {0, 255, 0, 255});
}

void update_scene_1(context_t* context) { change_scene(context, SCENE_A); }

void init_scene_2(context_t* context) {
  add_box(context, {200, 300}, {100, 150}, {255, 255, 0, 255});
}

void render_scene_2(context_t* context) {
  SDL_SetRenderDrawColor(context->renderer, 255, 0, 255, 255);
  SDL_RenderDrawLine(context->renderer, 0, 0, 200, 200);
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

  SDL_Window* window =
      SDL_CreateWindow("Deriv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       640, 480, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "Error failed to create window!\n";
    return 1;
  }

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  scene_t** scenes = create_scenes();

  context_t context;
  context.renderer = renderer;
  context.current_scene = SCENE_INIT;

  SDL_Event event;
  bool running = true;

  init_current_scene(&context, scenes[SCENE_INIT]);

  while (running) {
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

  SDL_Quit();

  return 0;
}
