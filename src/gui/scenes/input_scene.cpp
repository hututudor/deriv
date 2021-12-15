#include "input_scene.h"

#include <cstdio>

#include "../../ast/ast.h"
#include "../../ast/simplify.h"
#include "../../deriv/global.h"
#include "../../utils/ast_node_array.h"
#include "../utils/colors.h"
#include "../utils/screen.h"
#include "sidebar.h"

extern char func[1000];
extern node_t* ast;
extern node_t* ast_der;
extern char derivative[1000];

typedef struct {
  input_t* input;
  text_t* validation_text;
  text_t* derivative_label_text;
  text_t* derivative_text;
} input_scene_state_t;

bool is_function_valid(input_scene_state_t* state) {
  if (!strlen(state->input->content)) {
    return false;
  }

  FILE* in = fopen("TEMPFILEIN", "w");
  fwrite(state->input->content, 1, strlen(state->input->content), in);
  fclose(in);
  system("./build/cli TEMPFILEIN TEMPFILEOUT");

  remove("TEMPFILEIN");

  FILE* out = fopen("TEMPFILEOUT", "r");

  if (!out) {
    return false;
  }

  fseek(out, 0, SEEK_END);
  int size = ftell(out);
  fclose(out);

  remove("TEMPFILEOUT");

  return size > 0;
}

void derivate(void* context) {
  context_t* ctx = (context_t*)context;
  input_scene_state_t* state = (input_scene_state_t*)ctx->scene_state;

  strcpy(func, state->input->content);

  node_t* ast = parse_ast_from_string(func);
  simplify_ast(ast);

  node_t* ast_der = clone_ast(ast);
  Deriva(ast_der);
  simplify_ast(ast_der);

  strcpy(derivative, convert_ast_to_expression(ast_der));

  strcpy(state->derivative_text->content, derivative);
}

void derivate_callback(void* context) {
  context_t* ctx = (context_t*)context;
  input_scene_state_t* state = (input_scene_state_t*)ctx->scene_state;

  if (!is_function_valid(state)) {
    state->validation_text->color = COLOR_RED_VIVID_700;
    strcpy(state->validation_text->content,
           "The function is not correctly formatted!");

    strcpy(state->derivative_label_text->content, "");
    strcpy(state->derivative_text->content, "");
    return;
  }

  state->validation_text->color = COLOR_BLUE_VIVID_700;
  strcpy(state->validation_text->content,
         "The function is correctly formatted!");

  strcpy(state->derivative_label_text->content, "Derivative:");

  derivate(context);
}

void init_input_scene(context_t* context) {
  context->scene_state = malloc(sizeof(input_scene_state_t));
  input_scene_state_t* state = (input_scene_state_t*)context->scene_state;

  add_sidebar(context);

  add_text(context, "Please input a function:", {332, 40}, COLOR_COOL_GREY_900,
           false, true, 16, 0);

  add_input(context, {332, 54}, {SCREEN_WIDTH - 364, 44}, COLOR_COOL_GREY_900,
            COLOR_COOL_GREY_100, 16);

  state->input = &context->input_array->inputs[context->input_array->size - 1];

  add_button(context, "Derive function", {332, 106}, {200, 44},
             COLOR_BLUE_VIVID_050, COLOR_BLUE_VIVID_900, 16, derivate_callback);

  add_text(context, "", {564, 128}, COLOR_COOL_GREY_900, false, true, 16, 0);

  state->validation_text =
      &context->text_array->texts[context->text_array->size - 1];

  add_text(context, "", {332, 174}, COLOR_COOL_GREY_900, false, false, 16,
           SCREEN_WIDTH - 364);

  state->derivative_label_text =
      &context->text_array->texts[context->text_array->size - 1];

  add_text(context, "", {332, 198}, COLOR_COOL_GREY_900, false, false, 16,
           SCREEN_WIDTH - 364);

  state->derivative_text =
      &context->text_array->texts[context->text_array->size - 1];
}
