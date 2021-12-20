#include "translations.h"

char translations[TRANSLATION_COUNT][LANG_COUNT][TRANLATION_MAX_LENGTH];

void init_translations() {
  strcpy(translations[TRANSLATION_DERIV_FUNC][LANG_EN], "INPUT FUNCTION");
  strcpy(translations[TRANSLATION_DERIV_FUNC][LANG_RO], "INTRODUCERE FUNCTIE");
}