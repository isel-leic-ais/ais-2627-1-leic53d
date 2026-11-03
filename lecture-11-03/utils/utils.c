#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


void failure(const char *format, ...) {
	char msg[256];
	int n = sprintf(msg, "fatal error: ");
    va_list argList;
	
    va_start(argList, format);
    vsnprintf(msg+n, 256-n, format, argList);
    va_end(argList);
    fprintf(stderr, "%s\n", msg);
	exit(1);
}


void show_buffer(char buffer[], int size) {
    printf("[");
    if (size > 0) {
        printf("%c", buffer[0]);
        for(int i=1; i < size; ++i) {
            printf(", %c", buffer[i]);
        }
    }
    printf("]");
}