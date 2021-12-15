#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

#include "ast/ast.h"
#include "ast/simplify.h"
#include "deriv/global.h"
#include "gui/components/box.h"
#include "gui/components/input.h"
#include "gui/components/text.h"
#include "gui/scenes/about_scene.h"
#include "gui/scenes/ast_scene.h"
#include "gui/scenes/deriv_ast_scene.h"
#include "gui/scenes/input_scene.h"
#include "gui/utils/colors.h"
#include "gui/utils/scene.h"
#include "gui/utils/screen.h"
#include "utils/ast_node_array.h"
#include "utils/utils.h"

char func[1000] = "";
node_t* ast;
node_t* ast_der;
char derivative[1000] = "";

#define SCENE_COUNT 10

void update_scene_1(context_t* context) { change_scene(context, SCENE_ABOUT); }

scene_t** create_scenes() {
  scene_t** scenes = (scene_t**)calloc(sizeof(scene_t*), SCENE_COUNT);

  scenes[SCENE_INIT] = create_scene();
  scenes[SCENE_INIT]->update = update_scene_1;

  scenes[SCENE_ABOUT] = create_scene();
  scenes[SCENE_ABOUT]->init = init_about_scene;
  scenes[SCENE_ABOUT]->update = update_about_scene;

  scenes[SCENE_INPUT] = create_scene();
  scenes[SCENE_INPUT]->init = init_input_scene;

  scenes[SCENE_AST] = create_scene();
  scenes[SCENE_AST]->init = init_ast_scene;

  scenes[SCENE_DERIV_AST] = create_scene();
  scenes[SCENE_DERIV_AST]->init = init_deriv_ast_scene;

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
  context.want_to_exit = false;

  SDL_Event event;
  bool running = true;

  init_current_scene(&context, scenes[SCENE_INIT]);

  while (running) {
    SDL_PumpEvents();

    while (SDL_PollEvent(&event)) {
      running = event.type != SDL_QUIT;

      if (event.type == SDL_KEYDOWN) {
        global_handle_key_press_event(&context, event.key.keysym);
      }

      if (event.type == SDL_TEXTINPUT) {
        global_handle_text_input_event(&context, event.text);
      }
    }

    if (!running || context.want_to_exit) {
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
