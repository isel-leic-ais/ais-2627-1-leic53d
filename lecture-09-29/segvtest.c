/**
 * A segmentation violation scenario due 
 * to strtok use on a read/only string
 * 
 * We caught the SIGSEGV signal but there is nothing
 * we can do here to remedy the situation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "print_utils.h"

/**
 *  
 *  void (*signal( int signum, void (*handler)(int)))(int);
 * 
 *  typedef void (*sighandler_t)(int signum);
 * 
 *  sighandler_t signal(int signum, sighandler_t handler);
 */

 // uncomment the next line to show the effect of capture SIGSEGV signal
 // #define WITH_SIG_HANDLER

 #ifdef WITH_SIG_HANDLER
 typedef void (*sighandler_t)(int signum);
 
 
 void sig_handler(int signum) {
    // printf is not reentrant, so it is not safe in signal handlers.
    // You can use instead safe_printf defined in print_utils.c
    safe_printf("SIGSEGV ocurred!\n");
    exit(1);
 }
 #endif

int main() {
#ifdef WITH_SIG_HANDLER
    sighandler_t old_handler = signal(SIGSEGV, sig_handler);

    if (old_handler == SIG_DFL) {
        printf("old handler was SIG_DFL\n");
    } else if (old_handler == SIG_IGN) {
        printf("old handler was SIG_IGN\n");
    }
    else {
        printf("old handler was previously redefined\n");
    }
#endif   

    char *msg  = "a good day";
 
    char* tok = strtok(msg, " ");
    printf("first strtok done!\n");
    while(tok != NULL) {
        printf("tok=%s\n", tok);
        tok = strtok(NULL, " ");
    }
     
    printf("done!\n");
    return 0;
}
