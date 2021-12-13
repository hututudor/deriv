#include "text_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"

#define TEXT_ARRAY_ALLOC_SIZE 100

text_array_t* init_text_array() {
  text_array_t* array = (text_array_t*)malloc(sizeof(text_array_t));

  array->texts = (text_t*)malloc(sizeof(text_t) * TEXT_ARRAY_ALLOC_SIZE);
  array->max_size = TEXT_ARRAY_ALLOC_SIZE;
  array->size = 0;

  return array;
}

void destory_text_array(text_array_t* array) {
  while (array->size) {
    pop_text_array(array);
  }

  free(array->texts);
  free(array);
}

void push_text_array(text_array_t* array, text_t text) {
  if (array->size >= array->max_size) {
    array->texts = (text_t*)realloc(
        array->texts,
        sizeof(text_t) * (array->max_size + TEXT_ARRAY_ALLOC_SIZE));

    array->max_size += TEXT_ARRAY_ALLOC_SIZE;
  }

  array->texts[array->size].color = text.color;
  array->texts[array->size].pos = text.pos;
  array->texts[array->size].h_center = text.h_center;
  array->texts[array->size].v_center = text.v_center;
  array->texts[array->size].font = text.font;
  array->texts[array->size].content = (char*)malloc(strlen(text.content) + 1);

  strcpy(array->texts[array->size].content, text.content);

  array->size++;
}

text_t top_text_array(text_array_t* array) {
  if (array->size) {
    return array->texts[array->size - 1];
  }

  throw_error("trying to top an empty text stack");

  text_t text;
  return text;
}

text_t pop_text_array(text_array_t* array) {
  text_t top_text = top_text_array(array);

  array->size--;

  return top_text;
}

void render_text_array(void* context, text_array_t* array) {
  for (int i = 0; i < array->size; i++) {
    render_text(context, array->texts[i]);
  }
}