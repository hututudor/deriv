#include "deriv_ast_scene.h"

#include "../utils/colors.h"
#include "sidebar.h"

void init_deriv_ast_scene(context_t* context) {
  add_sidebar(context);
  add_text(context, "deriv ast", {332, 32}, COLOR_COOL_GREY_900, false, false,
           16, 0);
}

void update_deriv_ast_scene(context_t* context) { update_sidebar(context); }

void render_deriv_ast_scene(context_t* context) { render_sidebar(context); }

void destroy_deriv_ast_scene(context_t* context) { destroy_sidebar(context); }