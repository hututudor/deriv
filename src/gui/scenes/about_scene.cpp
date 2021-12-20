#include "about_scene.h"

#include "../utils/colors.h"
#include "../utils/screen.h"
#include "sidebar.h"

char description_header[] =
    "This program receives a mathematical function from the user and then, it "
    "calculates its derivation at any level requested. "
    "The derivation will be according to the x variable."
    "\nAn accepted function includes the most popular symbols in mathematics "
    "like: ^ for pow, * for multiplication, / for derivation, the number e, "
    "sqrt for square root, ln, log, trigonometric functions(sin, cos, tan, "
    "arccotan, etc), +, -.  Whenever possible, use parantheses to get the most "
    "accurate input."
    "\n\n\n\n\n\nAn example of a complex function is:";

char exemple_function[] = "\n\n((x+x^2)*(x+logx))^((x/lnx)-sqrt(x))";

char description_footer[] =
    "\nBehind the scenes, the application evaluates the expression received. "
    "Furthermore, it will provide an error if the input is wrong-written. "
    "Otherwise, it will continue the execution by simplifying the function and "
    "dividing it into tokens. They will serve as labels for the postfix tree, "
    "representing the expression."
    "The postfix tree is then visited node by node, applying the mathematical "
    "derivation rules wherever it meets a function not derivated yet."
    "\nAfter all the rules have been applied, the execution will call the "
    "simplified method again to make the postfix tree smaller. In the end, it "
    "will compute the derivated function from the postfix tree and will "
    "display it to the user."
    "The postfix tree for both: the function and the derivated function can be "
    "checked out by clicking on the corresponding button from the menu.";
typedef struct {
  text_t* description_header;
  text_t* exemple_function;
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

  add_text(context, "exemple_function", {640 + 32, 36 * 10},
           COLOR_ORANGE_VIVID_700, false, false, 18, 0);
  state->exemple_function =
      &context->text_array->texts[context->text_array->size - 1];

  add_text(context, "footer", {332 + 32, 36 * 12}, COLOR_COOL_GREY_900, false,
           false, 18, SCREEN_WIDTH - 332 - 32 * 4);
  state->description_footer =
      &context->text_array->texts[context->text_array->size - 1];
}

void update_about_scene(context_t* context) {
  update_sidebar(context);

  about_scene_state_t* state = (about_scene_state_t*)(context->scene_state);
  strcpy(state->description_header->content, description_header);
  strcpy(state->exemple_function->content, exemple_function);
  strcpy(state->description_footer->content, description_footer);
}

void render_about_scene(context_t* context) { render_sidebar(context); }

void destroy_about_scene(context_t* context) { destroy_sidebar(context); }