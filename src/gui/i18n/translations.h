#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include <string.h>

#define TRANLATION_MAX_LENGTH 4096

enum lang_type { LANG_EN, LANG_RO, LANG_COUNT };

enum translation_type {
  TRANSLATION_INPUT_SCENE,
  TRANSLATION_AST_SCENE,
  TRANSLATION_DERIV_AST_SCENE,
  TRANSLATION_ABOUT_SCENE,
  TRANSLATION_EXIT,
  TRANSLATION_MADE_BY,
  TRANSLATION_ABOUT_HEADER,
  TRANSLATION_ABOUT_FOOTER,
  TRANSLATION_FUNCTION_INPUT,
  TRANSLATION_ORDER_INPUT,
  TRANSLATION_COMPUTE_FIRST_ORDER,
  TRANSLATION_COMPUTE_CUSTOM_ORDER,
  TRANSLATION_FUNCTION_VALID,
  TRANSLATION_FUNCTION_INVALID,
  TRANSLATION_ORDER_VALID,
  TRANSLATION_ORDER_INVALID,
  TRANSLATION_FIRST_ORDER_DERIVATIVE,
  TRANSLATION_CUSTOM_ORDER_DERIVATIVE,
  TRANSLATION_NO_INPUT_FUNCTION,
  TRANSLATION_COUNT
};

extern char translations[TRANSLATION_COUNT][LANG_COUNT][TRANLATION_MAX_LENGTH];

void init_translations();

#endif