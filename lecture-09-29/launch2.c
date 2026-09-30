/**
 * show the effect od ControlC used to terminate 
 * a child process on the parent process without SIGINT handling
 * 
 */

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// uncomment next line to enable SIGINT catching
// #define WITH_SIG_HANDLER

#ifdef WITH_SIG_HANDLER
void sig_handler(int signo) {
    write(STDOUT_FILENO, "SIGINT!\n", 8);
}
#endif

int main(int argc, char *argv[]) {
#ifdef WITH_SIG_HANDLER    
    signal(SIGINT, sig_handler);
#endif
    if (argc < 2) {
        printf("sintax: launch cmd ...\n");
        exit(1);
    }

    pid_t child = fork();
    if (child < 0) {
        perror("error forking child");
        exit(1);
    }
    else if (child == 0) {
        printf("press enter to continue");
        getchar();
        printf("now launch!\n");
        execvp(argv[1], argv+1);
        char err_msg[256];
        sprintf(err_msg, "error execing %s", argv[1]);
        perror(err_msg);
        exit(1);
       
    }
    else {
        waitpid(child, NULL, 0);
    }
    
    printf("done!\n");
}
