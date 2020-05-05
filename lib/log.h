
#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <inc/const.h>

// Print a line of debug information.
#define debug(fmt, ...) _debug(fmt, __FILE__, __LINE__, __VA_ARGS__)
void _debug(const char* fmt, char* FILE, int LINE, ...);

// Throw an error out by the error code `err`.
// 
// Attention: `err` must be negative!
void fault(int err, int line, ...);

#endif