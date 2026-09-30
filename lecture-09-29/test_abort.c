#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc == 2) {
        printf("argv[1] is '%s'\n", argv[1]);
    }
    else {
        printf("Bad argument!\n");
        // abort is a function that raise a signal (SIGABRT)
        // on the current process (usefull for debugging)
        abort();
    }
    return 0;
}
