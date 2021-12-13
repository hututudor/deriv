#ifndef TEXT_ARRAY_H
#define TEXT_ARRAY_H

#include "../components/text.h"

typedef struct {
  text_t* texts;
  int size;
  int max_size;
} text_array_t;

text_array_t* init_text_array();
void destory_text_array(text_array_t* array);

void push_text_array(text_array_t* array, text_t text);
text_t top_text_array(text_array_t* array);
text_t pop_text_array(text_array_t* array);

void render_text_array(void* context, text_array_t* array);

#endif