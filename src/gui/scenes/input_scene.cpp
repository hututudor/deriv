#include "input_scene.h"

#include <cstdio>
#include <cstdlib>

#include "../../ast/ast.h"
#include "../../ast/simplify.h"
#include "../../deriv/global.h"
#include "../../utils/ast_node_array.h"
#include "../i18n/i18n.h"
#include "../utils/colors.h"
#include "../utils/screen.h"
#include "sidebar.h"

extern char func[1000];
extern node_t* ast;
extern node_t* ast_der;
extern char derivative[1000];
extern int derivative_order;

typedef struct {
  input_t* input_order;
  text_t* order_validation_text;
  input_t* input;
  text_t* validation_text;
  text_t* derivative_label_text;
  text_t* derivative_text;

  text_t* label_function_input_text;
  text_t* button_function_input_text;
  text_t* label_order_input_text;
  text_t* button_order_input_text;
} input_scene_state_t;

bool cmp_color(color_t a, color_t b) {
  return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

bool is_function_valid(input_scene_state_t* state) {
  if (!strlen(state->input->content)) {
    return false;
  }

  FILE* in = fopen("TEMPFILEIN", "w");
  fwrite(state->input->content, 1, strlen(state->input->content), in);
  fclose(in);

#ifdef _WIN32
  system(".\\build\\cli TEMPFILEIN TEMPFILEOUT");
#else
  system("./build/cli TEMPFILEIN TEMPFILEOUT");
#endif

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

void derivate_with_order(void* context, int order) {
  context_t* ctx = (context_t*)context;
  input_scene_state_t* state = (input_scene_state_t*)ctx->scene_state;

  strcpy(func, state->input->content);

  ast = parse_ast_from_string(func);
  simplify_ast(ast);

  ast_der = clone_ast(ast);
  for (int i = 0; i < order; i++) {
    Deriva(ast_der);
    simplify_ast(ast_der);
  }

  strcpy(derivative, convert_ast_to_expression(ast_der));

  strcpy(state->derivative_text->content, derivative);

  derivative_order = order;
}

void derivate_callback(void* context) {
  context_t* ctx = (context_t*)context;
  input_scene_state_t* state = (input_scene_state_t*)ctx->scene_state;

  if (!is_function_valid(state)) {
    state->validation_text->color = COLOR_RED_VIVID_700;
    strcpy(state->validation_text->content,
           get_i18n_string(TRANSLATION_FUNCTION_INVALID));

    strcpy(state->derivative_label_text->content, "");
    strcpy(state->derivative_text->content, "");
    return;
  }

  state->validation_text->color = COLOR_BLUE_VIVID_700;
  strcpy(state->validation_text->content,
         get_i18n_string(TRANSLATION_FUNCTION_VALID));

  strcpy(state->derivative_label_text->content,
         get_i18n_string(TRANSLATION_FIRST_ORDER_DERIVATIVE));

  derivate_with_order(context, 1);
}

void order_callback(void* context) {
  context_t* ctx = (context_t*)context;
  input_scene_state_t* state = (input_scene_state_t*)ctx->scene_state;

  if (!is_function_valid(state)) {
    state->validation_text->color = COLOR_RED_VIVID_700;
    strcpy(state->validation_text->content,
           get_i18n_string(TRANSLATION_FUNCTION_INVALID));

    strcpy(state->derivative_label_text->content, "");
    strcpy(state->derivative_text->content, "");
    return;
  }

  int order = atoi(state->input_order->content);

  if (order < 1) {
    state->order_validation_text->color = COLOR_RED_VIVID_700;
    strcpy(state->order_validation_text->content,
           get_i18n_string(TRANSLATION_ORDER_INVALID));

    strcpy(state->derivative_label_text->content, "");
    strcpy(state->derivative_text->content, "");
    return;
  }

  state->order_validation_text->color = COLOR_BLUE_VIVID_700;
  strcpy(state->order_validation_text->content,
         get_i18n_string(TRANSLATION_ORDER_VALID));

  state->validation_text->color = COLOR_BLUE_VIVID_700;
  strcpy(state->validation_text->content,
         get_i18n_string(TRANSLATION_FUNCTION_VALID));

  if (order == 1) {
    strcpy(state->derivative_label_text->content,
           get_i18n_string(TRANSLATION_FIRST_ORDER_DERIVATIVE));
  } else {
    strcpy(state->derivative_label_text->content,
           get_i18n_f_string(TRANSLATION_CUSTOM_ORDER_DERIVATIVE, order));
  }

  derivate_with_order(context, order);
}

void init_input_scene(context_t* context) {
  context->scene_state = malloc(sizeof(input_scene_state_t));
  input_scene_state_t* state = (input_scene_state_t*)context->scene_state;

  add_sidebar(context);

  add_text(context, get_i18n_string(TRANSLATION_FUNCTION_INPUT), {332, 40},
           COLOR_COOL_GREY_900, false, true, 16, 0);

  state->label_function_input_text =
      &context->text_array->texts[context->text_array->size - 1];

  add_input(context, {332, 54}, {SCREEN_WIDTH - 364, 44}, COLOR_COOL_GREY_900,
            COLOR_COOL_GREY_100, 16);

  state->input = &context->input_array->inputs[context->input_array->size - 1];

  state->input->is_focused = true;
  state->input->callback = derivate_callback;

  add_button(context, get_i18n_string(TRANSLATION_COMPUTE_FIRST_ORDER),
             {332, 106}, {300, 44}, COLOR_BLUE_VIVID_050, COLOR_BLUE_VIVID_900,
             16, derivate_callback);

  state->button_function_input_text =
      &context->text_array->texts[context->text_array->size - 1];

  add_text(context, "", {664, 128}, COLOR_COOL_GREY_900, false, true, 16, 0);

  state->validation_text =
      &context->text_array->texts[context->text_array->size - 1];

  // order
  add_text(context, get_i18n_string(TRANSLATION_ORDER_INPUT), {332, 174},
           COLOR_COOL_GREY_900, false, true, 16, 0);

  state->label_order_input_text =
      &context->text_array->texts[context->text_array->size - 1];

  add_input(context, {332, 188}, {SCREEN_WIDTH - 364, 44}, COLOR_COOL_GREY_900,
            COLOR_COOL_GREY_100, 16);

  state->input_order =
      &context->input_array->inputs[context->input_array->size - 1];

  state->input_order->callback = order_callback;

  add_button(context, get_i18n_string(TRANSLATION_COMPUTE_CUSTOM_ORDER),
             {332, 242}, {300, 44}, COLOR_BLUE_VIVID_050, COLOR_BLUE_VIVID_900,
             16, order_callback);

  state->button_order_input_text =
      &context->text_array->texts[context->text_array->size - 1];

  add_text(context, "", {664, 264}, COLOR_COOL_GREY_900, false, true, 16, 0);

  state->order_validation_text =
      &context->text_array->texts[context->text_array->size - 1];

  // derivative
  add_text(context, "", {332, 310}, COLOR_COOL_GREY_900, false, false, 16,
           SCREEN_WIDTH - 364);

  state->derivative_label_text =
      &context->text_array->texts[context->text_array->size - 1];

  add_text(context, "", {332, 334}, COLOR_COOL_GREY_900, false, false, 16,
           SCREEN_WIDTH - 364);

  state->derivative_text =
      &context->text_array->texts[context->text_array->size - 1];

  if (derivative_order) {
    char* order_str = (char*)calloc(1, 1000);
    sprintf(order_str, "%d", derivative_order);

    strcpy(state->input_order->content, order_str);
    free(order_str);
  }

  if (strlen(func)) {
    strcpy(state->input->content, func);
  }

  if (strlen(derivative)) {
    strcpy(state->derivative_text->content, derivative);

    if (derivative_order == 1) {
      strcpy(state->derivative_label_text->content,
             get_i18n_string(TRANSLATION_FIRST_ORDER_DERIVATIVE));
    } else {
      strcpy(state->derivative_label_text->content,
             get_i18n_f_string(TRANSLATION_CUSTOM_ORDER_DERIVATIVE,
                               derivative_order));
    }
  }
}

void update_input_scene(context_t* context) {
  update_sidebar(context);

  input_scene_state_t* state = (input_scene_state_t*)context->scene_state;

  strcpy(state->label_function_input_text->content,
         get_i18n_string(TRANSLATION_FUNCTION_INPUT));

  strcpy(state->button_function_input_text->content,
         get_i18n_string(TRANSLATION_COMPUTE_FIRST_ORDER));

  strcpy(state->label_order_input_text->content,
         get_i18n_string(TRANSLATION_ORDER_INPUT));

  strcpy(state->button_order_input_text->content,
         get_i18n_string(TRANSLATION_COMPUTE_CUSTOM_ORDER));

  if (strlen(state->validation_text->content)) {
    if (cmp_color(state->validation_text->color, COLOR_RED_VIVID_700)) {
      strcpy(state->validation_text->content,
             get_i18n_string(TRANSLATION_FUNCTION_INVALID));
    } else {
      strcpy(state->validation_text->content,
             get_i18n_string(TRANSLATION_FUNCTION_VALID));
    }
  }

  if (strlen(state->order_validation_text->content)) {
    if (cmp_color(state->order_validation_text->color, COLOR_RED_VIVID_700)) {
      strcpy(state->order_validation_text->content,
             get_i18n_string(TRANSLATION_ORDER_INVALID));
    } else {
      strcpy(state->order_validation_text->content,
             get_i18n_string(TRANSLATION_ORDER_VALID));
    }
  }

  if (strlen(state->derivative_label_text->content)) {
    if (derivative_order == 1) {
      strcpy(state->derivative_label_text->content,
             get_i18n_string(TRANSLATION_FIRST_ORDER_DERIVATIVE));
    } else {
      strcpy(state->derivative_label_text->content,
             get_i18n_f_string(TRANSLATION_CUSTOM_ORDER_DERIVATIVE,
                               derivative_order));
    }
  }
}

void render_input_scene(context_t* context) { render_sidebar(context); }

void destroy_input_scene(context_t* context) { destroy_sidebar(context); }
