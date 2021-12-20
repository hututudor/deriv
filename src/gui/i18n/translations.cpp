#include "translations.h"

char translations[TRANSLATION_COUNT][LANG_COUNT][TRANLATION_MAX_LENGTH];

void init_translations() {
  strcpy(translations[TRANSLATION_INPUT_SCENE][LANG_EN], "INPUT FUNCTION");
  strcpy(translations[TRANSLATION_INPUT_SCENE][LANG_RO], "INTRODUCERE FUNCTIE");

  strcpy(translations[TRANSLATION_AST_SCENE][LANG_EN], "VIEW NODE TREE");
  strcpy(translations[TRANSLATION_AST_SCENE][LANG_RO], "VEZI ARBORELE SIMPLU");

  strcpy(translations[TRANSLATION_DERIV_AST_SCENE][LANG_EN],
         "VIEW DERIVATE TREE");
  strcpy(translations[TRANSLATION_DERIV_AST_SCENE][LANG_RO],
         "VEZI ARBORELE DERIVAT");

  strcpy(translations[TRANSLATION_ABOUT_SCENE][LANG_EN], "ABOUT");
  strcpy(translations[TRANSLATION_ABOUT_SCENE][LANG_RO], "DESPRE");

  strcpy(translations[TRANSLATION_EXIT][LANG_EN], "EXIT");
  strcpy(translations[TRANSLATION_EXIT][LANG_RO], "IESIRE");

  strcpy(translations[TRANSLATION_MADE_BY][LANG_EN], "Made by ");
  strcpy(translations[TRANSLATION_MADE_BY][LANG_RO], "Facut de ");
}