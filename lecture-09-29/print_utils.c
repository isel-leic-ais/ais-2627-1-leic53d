#include <unistd.h>
#include "stdio.h" 
#include <fcntl.h>
#include <stdarg.h>


void perror2(const char *format, ...) {
	char msg[256];
    va_list argList;
	
    va_start(argList, format);
    vsnprintf(msg, 256, format, argList);
    va_end(argList);
    perror(msg);
}

/**
 * A reentrant version of printf, useful for use 
 * in signal handlers
 */
int safe_printf(const char *format, ...) {
	char msg[1024];
    va_list argList;
	
    va_start(argList, format);
    int total_chars = vsnprintf(msg, 1024, format, argList);
    va_end(argList);
    write(STDOUT_FILENO, msg, total_chars);
    return total_chars;
}

