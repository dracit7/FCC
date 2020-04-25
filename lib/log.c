
#include <lib/log.h>

void logger(const char* fmt, const char* type, 
  char* FILE, int LINE, ...) {

  // Show the loghead
  if (FILE[0] == 0) 
    printf("[%s] ", type);
  else
    printf("[%s] <%s:%d> ", type, FILE, LINE);

  // Print user_defined message
  va_list args;
  va_start(args, LINE);
  vprintf(fmt, args);
  va_end(args);

  putchar('\n');
}