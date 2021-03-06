#include "io.h"

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstring>

#include "utils.h"

char* read_entire_file(char* path) {
  FILE* file = fopen(path, "r");

  if (!file) {
    throw_error("file not found: %s", path);
  }

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(size + 1);

  if (!buffer) {
    throw_error("cannot alloc buffer for file");
  }

  if (!fread(buffer, size, 1, file)) {
    free(buffer);
    throw_error("cannot read file");
  }

  fclose(file);
  return buffer;
}

void write_entire_file(char* path, char* data) {
  FILE* file = fopen(path, "w");

  if (!file) {
    throw_error("file not found: %s", path);
  }

  if (!fwrite(data, 1, strlen(data), file)) {
    throw_error("cannot write file");
  }

  fclose(file);
}