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

  strcpy(translations[TRANSLATION_FUNCTION_INPUT][LANG_EN],
         "Please input a function: ");
  strcpy(translations[TRANSLATION_FUNCTION_INPUT][LANG_RO],
         "Introdu o functie: ");

  strcpy(translations[TRANSLATION_ORDER_INPUT][LANG_EN],
         "Please input a custom derivative order: ");
  strcpy(translations[TRANSLATION_ORDER_INPUT][LANG_RO],
         "Introdu un ordin de derivare: ");

  strcpy(translations[TRANSLATION_COMPUTE_FIRST_ORDER][LANG_EN],
         "Compute first order derivative");
  strcpy(translations[TRANSLATION_COMPUTE_FIRST_ORDER][LANG_RO],
         "Caluleaza prima derivata");

  strcpy(translations[TRANSLATION_COMPUTE_CUSTOM_ORDER][LANG_EN],
         "Compute custom order derivative");
  strcpy(translations[TRANSLATION_COMPUTE_CUSTOM_ORDER][LANG_RO],
         "Caluleaza derivata de ordinul specificat");

  strcpy(translations[TRANSLATION_FUNCTION_VALID][LANG_EN],
         "The function is correctly formatted!");
  strcpy(translations[TRANSLATION_FUNCTION_VALID][LANG_RO],
         "Functia este scrisa corect!");

  strcpy(translations[TRANSLATION_FUNCTION_INVALID][LANG_EN],
         "The function is not correctly formatted!");
  strcpy(translations[TRANSLATION_FUNCTION_INVALID][LANG_RO],
         "Functia nu este scrisa corect!");

  strcpy(translations[TRANSLATION_ORDER_VALID][LANG_EN],
         "The order is a valid number!");
  strcpy(translations[TRANSLATION_ORDER_VALID][LANG_RO],
         "Ordinul este un numar valid!");

  strcpy(translations[TRANSLATION_ORDER_INVALID][LANG_EN],
         "The order is not a valid number!");
  strcpy(translations[TRANSLATION_ORDER_INVALID][LANG_RO],
         "Ordinul nu este un numar valid!");

  strcpy(translations[TRANSLATION_FIRST_ORDER_DERIVATIVE][LANG_EN],
         "First order derivative:");
  strcpy(translations[TRANSLATION_FIRST_ORDER_DERIVATIVE][LANG_RO],
         "Prima derivata:");

  strcpy(translations[TRANSLATION_CUSTOM_ORDER_DERIVATIVE][LANG_EN],
         "Derivative of the %dth order:");
  strcpy(translations[TRANSLATION_CUSTOM_ORDER_DERIVATIVE][LANG_RO],
         "Derivata de ordinul %d:");

  strcpy(translations[TRANSLATION_NO_INPUT_FUNCTION][LANG_EN],
         "No input function!");
  strcpy(translations[TRANSLATION_NO_INPUT_FUNCTION][LANG_RO],
         "Nu ai introdus o functie!");

  strcpy(
      translations[TRANSLATION_ABOUT_HEADER][LANG_EN],
      "This program receives a mathematical function from the user and then, "
      "it calculates its derivation for any order requested. The derivation "
      "will be done according to the x variable.\nAn accepted function "
      "includes the "
      "most popular symbols in mathematics like: ^ for pow, * for "
      "multiplication, / for division, the number e, sqrt for square root, ln, "
      "log, trigonometric functions(sin, cos, tan, arccotan, etc), +, -.  "
      "Whenever possible, use parantheses to get the most accurate "
      "input.\n\n\n\n\n\nAn example of a complex function is:");

  strcpy(
      translations[TRANSLATION_ABOUT_HEADER][LANG_RO],
      "Programul primeste o functie matematica de la utilizator si apoi "
      "calculeaza derivarea acesteia pentru orice ordin solicitat. Derivarea "
      "va fi fcuta conform variabilei x. \nO functie acceptata include "
      "principalele "
      "simboluri din matematica cum ar fi: ^ pentru ridicarea la putere, * "
      "pentru inmultire, / pentru impartire, numarul e, sqrt pentru radacina "
      "patrata, ln, log, functii trigonometrice(sin, cos, tan, arccotan, etc), "
      "+, -. Ori de cate ori este posibil, utilizati paranteze pentru a obtine "
      "cel mai precis rezultat."
      "\n\n\n\n\nUn exemplu de functie complexa este:");

  strcpy(
      translations[TRANSLATION_ABOUT_FOOTER][LANG_EN],
      "\nBehind the scenes, the application evaluates the expression received. "
      "Furthermore, it will provide an error if the input is wrong-written. "
      "Otherwise, it will continue the execution by simplifying the function "
      "and dividing it into tokens. They will serve as labels for the postfix "
      "tree, representing the expression.The postfix tree is then visited node "
      "by node, applying the mathematical derivation rules wherever it meets a "
      "function not derivated yet.\nAfter all the rules have been applied, the "
      "execution will call the simplified method again to make the postfix "
      "tree smaller. In the end, it will compute the derivated function from "
      "the postfix tree and will display it to the user.The node tree for "
      "both: the function and the derivated function can be checked out by "
      "clicking on the corresponding button from the menu.");

  strcpy(
      translations[TRANSLATION_ABOUT_FOOTER][LANG_RO],
      "\nIn spate, aplicatia evalueaza expresia primita. In plus, va furniza "
      "o eroare daca functia este scrisa gresit. In caz contrar, va "
      "continua executia simplificand functia si impartind-o in token-uri. "
      "Acestea vor avea rol de etichete pentru arborele postfix, "
      "reprezentand expresia. Arborele postfix este apoi vizitat nod cu "
      "nod, aplicand regulile de derivare matematica oriunde intalneste o "
      "expresie nederivata inca.\nDupa ce toate regulile au fost aplicate, "
      "executia va apela din nou metoda simplificata pentru a face arborele "
      "postfix mai mic. In cele din urma, va calcula functia derivata din "
      "arborele postfix si o va afisa utilizatorului. Arborele de noduri "
      "atat pentru functia in sine si derivata pot fi verificate facand "
      "clic pe butonul corespunzator din meniu.");
}