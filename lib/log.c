
#include <lib/log.h>

void _debug(const char* fmt, char* FILE, int LINE, ...) {
  printf("[DEBUG] <%s:%d> ", FILE, LINE);

  va_list args;
  va_start(args, LINE);
  vprintf(fmt, args);
  va_end(args);
  putchar('\n');
}

void fault(int err, int line, ...) {
  if (!line) printf("<%s> Error: ", error_src[-err]);
  else printf("<%s> Error (line %d): ", error_src[-err], line);

  va_list args;
  va_start(args, line);
  vprintf(error_msg[-err], args);
  va_end(args);
  putchar('\n');
}