#include "string.h"

#include <memory.h>
#include <stdlib.h>

#define STRING_ALLOC_SIZE 1000

string_t* init_string() {
  string_t* string = (string_t*)malloc(sizeof(string_t));

  string->data = (char*)malloc(sizeof(char) * STRING_ALLOC_SIZE);
  string->size = 0;
  string->max_size = STRING_ALLOC_SIZE;

  return string;
}

void destory_string(string_t* string) {
  free(string->data);
  free(string);
}

void concat_string(string_t* string, char* cstring) {
  int size = strlen(cstring);

  if (string->size + size > string->max_size) {
    int segments = size / STRING_ALLOC_SIZE + 1;

    string->data = (char*)realloc(
        string->data, string->max_size + segments * STRING_ALLOC_SIZE);

    string->max_size += segments * STRING_ALLOC_SIZE;
  }

  for (int i = 0; i < size; i++) {
    string->data[string->size++] = cstring[i];
  }
}

void concat_const_string(string_t* string, const char* cstring) {
  int size = strlen(cstring);

  char* cstr = (char*)malloc(size + 1);
  memset(cstr, 0, size + 1);

  for (int i = 0; i < size; i++) {
    cstr[i] = cstring[i];
  }

  concat_string(string, cstr);
}

char* get_c_string(string_t* string) {
  char* cstring = (char*)malloc(string->size + 1);
  memset(cstring, 0, string->size + 1);

  for (int i = 0; i < string->size; i++) {
    cstring[i] = string->data[i];
  }

  return cstring;
}
