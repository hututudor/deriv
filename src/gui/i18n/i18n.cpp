#include "i18n.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

lang_type current_lang = LANG_EN;

lang_type get_i18n_lang() { return current_lang; }

void set_i18n_lang(lang_type lang) { current_lang = lang; }

const char* get_i18n_string(translation_type type) {
  return translations[type][current_lang];
}

const char* get_i18n_f_string(translation_type type, ...) {
  char* fmt = translations[type][current_lang];
  char* buffer = (char*)malloc(4096);

  va_list args;
  va_start(args, type);

  vsprintf(buffer, fmt, args);

  va_end(args);

  return buffer;
}