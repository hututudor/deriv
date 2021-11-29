#include "utils.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void throw_error(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  printf("ERROR: ");
  vprintf(fmt, args);
  printf("\n");

  va_end(args);
  exit(-1);
}