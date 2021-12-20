#ifndef I18N_H
#define I18N_H

#include "translations.h"

lang_type get_i18n_lang();
void set_i18n_lang(lang_type lang);

const char* get_i18n_string(translation_type type);
const char* get_i18n_f_string(translation_type type, ...);

#endif