#include "about_scene.h"

#include "../i18n/i18n.h"
#include "../utils/colors.h"
#include "../utils/screen.h"
#include "sidebar.h"

char example_function[] = "\n\n((x+x^2)*(x+logx))^((x/lnx)-sqrt(x))";

typedef struct {
  text_t* description_header;
  text_t* example_function;
  text_t* description_footer;
} about_scene_state_t;

void init_about_scene(context_t* context) {
  context->scene_state = malloc(sizeof(about_scene_state_t));
  about_scene_state_t* state = (about_scene_state_t*)context->scene_state;

  add_sidebar(context);

  add_text(context, "header", {332 + 32, 36 * 3}, COLOR_COOL_GREY_900, false,
           false, 18, SCREEN_WIDTH - 332 - 32 * 4);
  state->description_header =
      &context->text_array->texts[context->text_array->size - 1];

  add_text(context, "example_function", {640 + 32, 36 * 10},
           COLOR_ORANGE_VIVID_700, false, false, 18, 0);
  state->example_function =
      &context->text_array->texts[context->text_array->size - 1];

  add_text(context, "footer", {332 + 32, 36 * 12}, COLOR_COOL_GREY_900, false,
           false, 18, SCREEN_WIDTH - 332 - 32 * 4);
  state->description_footer =
      &context->text_array->texts[context->text_array->size - 1];
}

void update_about_scene(context_t* context) {
  update_sidebar(context);

  about_scene_state_t* state = (about_scene_state_t*)(context->scene_state);

  strcpy(state->description_header->content,
         get_i18n_string(TRANSLATION_ABOUT_HEADER));

  strcpy(state->example_function->content, example_function);

  strcpy(state->description_footer->content,
         get_i18n_string(TRANSLATION_ABOUT_FOOTER));
}

void render_about_scene(context_t* context) { render_sidebar(context); }

void destroy_about_scene(context_t* context) { destroy_sidebar(context); }