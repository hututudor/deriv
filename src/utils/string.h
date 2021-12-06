#ifndef STRING_H
#define STRING_H

typedef struct {
  char* data;
  int size;
  int max_size;
} string_t;

string_t* init_string();
void destory_string(string_t* string);

void concat_string(string_t* string, char* cstring);
void concat_const_string(string_t* string, const char* cstring);
char* get_c_string(string_t* string);

#endif