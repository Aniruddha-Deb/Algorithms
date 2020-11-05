#include "logger.h"

#include <stdio.h>
#include <stdarg.h>

void log_debug(char* fmt, ...) {
	#ifdef DEBUG
		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
	#endif
}
