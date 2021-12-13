#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "gui/components/box.h"
#include "gui/components/text.h"
#include "gui/scenes/about_scene.h"
#include "gui/utils/colors.h"
#include "gui/utils/scene.h"
#include "gui/utils/screen.h"
#include "utils/utils.h"

#define SCENE_COUNT 10

void update_scene_1(context_t* context) { change_scene(context, SCENE_ABOUT); }

char func[100] = "x ^ 2 + sin(x)";

scene_t** create_scenes() {
  scene_t** scenes = (scene_t**)calloc(sizeof(scene_t*), SCENE_COUNT);

  scenes[SCENE_INIT] = create_scene();
  scenes[SCENE_INIT]->update = update_scene_1;

  scenes[SCENE_ABOUT] = create_scene();
  scenes[SCENE_ABOUT]->init = init_about_scene;
  scenes[SCENE_ABOUT]->update = update_about_scene;

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
  srand(time(NULL));

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

  SDL_Window* window =
      SDL_CreateWindow("Deriv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    throw_error("could not create window");
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  scene_t** scenes = create_scenes();

  context_t context;
  context.scene_state = nullptr;
  context.renderer = renderer;
  context.current_scene = SCENE_INIT;

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
