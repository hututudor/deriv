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

void log(const char* fmt, ...) {
#ifdef DEBUG_LOG

  va_list args;
  va_start(args, fmt);

  vprintf(fmt, args);

  va_end(args);

#endif
}