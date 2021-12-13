#include "input_scene.h"

#include "../utils/colors.h"
#include "sidebar.h"

void init_input_scene(context_t* context) {
  add_sidebar(context);
  add_text(context, "input", {332, 32}, COLOR_COOL_GREY_900, false, false, 16);
}
