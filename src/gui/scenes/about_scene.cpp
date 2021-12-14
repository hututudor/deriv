#include "about_scene.h"

#include "../utils/colors.h"
#include "sidebar.h"

extern char func[1000];

typedef struct {
  text_t* func_text;
} about_scene_state_t;

void init_about_scene(context_t* context) {
  context->scene_state = malloc(sizeof(about_scene_state_t));

  add_sidebar(context);
  add_text(context, "func", {332, 32}, COLOR_COOL_GREY_900, false, false, 16,
           0);

  about_scene_state_t* state = (about_scene_state_t*)(context->scene_state);
  state->func_text = &context->text_array->texts[context->text_array->size - 1];
}

void update_about_scene(context_t* context) {
  about_scene_state_t* state = (about_scene_state_t*)(context->scene_state);
  strcpy(state->func_text->content, func);
}