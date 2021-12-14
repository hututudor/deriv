#include "sidebar.h"

#include "../components/box.h"
#include "../components/button.h"
#include "../components/text.h"
#include "../utils/colors.h"
#include "../utils/context.h"
#include "../utils/scene.h"
#include "../utils/screen.h"

char names[2][30] = {"Tudor Hutu", "Cristian Roman"};
char made_by_str[100];

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

void add_sidebar(context_t* context) {
  // background
  add_box(context, {0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT}, COLOR_COOL_GREY_050);

  // sidebar
  add_box(context, {0, 0}, {300, SCREEN_HEIGHT}, COLOR_COOL_GREY_800);
  add_box(context, {0, 0}, {300, 100}, COLOR_COOL_GREY_300);
  add_text(context, "Deriv", {150, 50}, COLOR_BLUE_VIVID_900, true, true, 48,
           0);

  // buttons
  add_button(context, "INPUT FUNCTION", {32, 150 + 32 * 1}, {236, 44},
             COLOR_BLUE_VIVID_900, COLOR_BLUE_VIVID_050, 16,
             input_scene_callback);

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