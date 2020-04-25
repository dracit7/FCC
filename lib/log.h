
#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define debug(fmt, ...) logger(fmt, "DEBUG", __FILE__, __LINE__, __VA_ARGS__)
#define info(fmt, ...) logger(fmt, "INFO", "", 0, __VA_ARGS__)
#define fault(fmt, ...) do {\
  logger(fmt, "ERROR", "", 0, __VA_ARGS__);\
  exit(1);\
} while (0)

void logger(
  const char* fmt, const char* type, 
  char* FILE, int LINE, ...);

#endif