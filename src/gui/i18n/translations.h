#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include <string.h>

#define TRANLATION_MAX_LENGTH 4096

enum lang_type { LANG_EN, LANG_RO, LANG_COUNT };

enum translation_type { TRANSLATION_DERIV_FUNC, TRANSLATION_COUNT };

extern char translations[TRANSLATION_COUNT][LANG_COUNT][TRANLATION_MAX_LENGTH];

void init_translations();

#endif