#include "sidebar.h"

#include <SDL2/SDL_image.h>

#include "../components/box.h"
#include "../components/button.h"
#include "../components/text.h"
#include "../i18n/i18n.h"
#include "../utils/colors.h"
#include "../utils/context.h"
#include "../utils/scene.h"
#include "../utils/screen.h"

char names[2][30] = {"Tudor Hutu", "Cristian Roman"};
char made_by_str[100];

typedef struct {
  SDL_Texture* ro_flag;
  SDL_Texture* en_flag;
} sidebar_state_t;

void input_scene_callback(void* context) {
  change_scene((context_t*)context, SCENE_INPUT);
}

void ast_scene_callback(void* context) {
  change_scene((context_t*)context, SCENE_AST);
}

void deriv_ast_scene_callback(void* context) {
  change_scene((context_t*)context, SCENE_DERIV_AST);
}

void about_scene_callback(void* context) {
  change_scene((context_t*)context, SCENE_ABOUT);
}

void exit_callback(void* context) {
  context_t* ctx = (context_t*)context;
  ctx->want_to_exit = true;
}

void lang_callback(void* context) {
  if (get_i18n_lang() == LANG_EN) {
    set_i18n_lang(LANG_RO);
  } else {
    set_i18n_lang(LANG_EN);
  }
}

void add_sidebar(context_t* context) {
  context->extra_state = (sidebar_state_t*)malloc(sizeof(sidebar_state_t));
  sidebar_state_t* state = (sidebar_state_t*)context->extra_state;

  SDL_Surface* ro = IMG_Load("res/ro.png");
  state->ro_flag = SDL_CreateTextureFromSurface(context->renderer, ro);
  SDL_FreeSurface(ro);

  SDL_Surface* en = IMG_Load("res/en.png");
  state->en_flag = SDL_CreateTextureFromSurface(context->renderer, en);
  SDL_FreeSurface(en);

  // background
  add_box(context, {0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT}, COLOR_COOL_GREY_050);

  // sidebar
  add_box(context, {0, 0}, {300, SCREEN_HEIGHT}, COLOR_COOL_GREY_800);
  add_box(context, {0, 0}, {300, 100}, COLOR_COOL_GREY_300);
  add_text(context, "Deriv", {150, 50}, COLOR_BLUE_VIVID_900, true, true, 48,
           0);

  // buttons
  add_button(context, get_i18n_string(TRANSLATION_DERIV_FUNC),
             {32, 150 + 32 * 1}, {236, 44}, COLOR_BLUE_VIVID_900,
             COLOR_BLUE_VIVID_050, 16, input_scene_callback);

  add_button(context, "VIEW NODE TREE", {32, 150 + 32 * 2 + 44 * 1}, {236, 44},
             COLOR_BLUE_VIVID_900, COLOR_BLUE_VIVID_050, 16,
             ast_scene_callback);

  add_button(context, "VIEW DERIVATE TREE", {32, 150 + 32 * 3 + 44 * 2},
             {236, 44}, COLOR_BLUE_VIVID_900, COLOR_BLUE_VIVID_050, 16,
             deriv_ast_scene_callback);

  add_button(context, "ABOUT", {32, 150 + 32 * 4 + 44 * 3}, {236, 44},
             COLOR_BLUE_VIVID_900, COLOR_BLUE_VIVID_050, 16,
             about_scene_callback);

  add_button(context, "EXIT", {32, 150 + 32 * 5 + 44 * 4}, {236, 44},
             COLOR_BLUE_VIVID_900, COLOR_BLUE_VIVID_050, 16, exit_callback);

  // lang
  add_button(context, "", {126, 150 + 32 * 6 + 44 * 5}, {48, 48},
             COLOR_COOL_GREY_800, COLOR_COOL_GREY_800, 1, lang_callback);

  // footer
  add_box(context, {0, SCREEN_HEIGHT - 50}, {300, 50}, COLOR_COOL_GREY_900);

  if (!strlen(made_by_str)) {
    strcpy(made_by_str, "Made by ");

    int first = rand() % 2;

    strcat(made_by_str, names[first]);
    strcat(made_by_str, " & ");
    strcat(made_by_str, names[1 - first]);
  }

  add_text(context, made_by_str, {150, SCREEN_HEIGHT - 25}, COLOR_COOL_GREY_050,
           true, true, 16, 0);
}

void update_sidebar(context_t* context) {
  // TODO(tudor): update lang specifically
}

void render_sidebar(context_t* context) {
  sidebar_state_t* state = (sidebar_state_t*)context->extra_state;

  SDL_Rect dst;
  dst.x = 126;
  dst.y = 150 + 32 * 6 + 44 * 5;
  dst.w = 48;
  dst.h = 48;

  if (get_i18n_lang() == LANG_EN) {
    SDL_RenderCopy(context->renderer, state->en_flag, NULL, &dst);
  } else {
    SDL_RenderCopy(context->renderer, state->ro_flag, NULL, &dst);
  }
}

void destroy_sidebar(context_t* context) {
  sidebar_state_t* state = (sidebar_state_t*)context->extra_state;

  SDL_DestroyTexture(state->en_flag);
  SDL_DestroyTexture(state->ro_flag);
}