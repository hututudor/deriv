#ifndef LINE_ARRAY_H
#define LINE_ARRAY_H

#include "../components/line.h"

typedef struct {
  line_t* lines;
  int size;
  int max_size;
} line_array_t;

line_array_t* init_line_array();
void destory_line_array(line_array_t* array);

void push_line_array(line_array_t* array, line_t line);
line_t top_line_array(line_array_t* array);
line_t pop_line_array(line_array_t* array);

void update_line_array(void* context, line_array_t* array);
void render_line_array(void* context, line_array_t* array);

#endif