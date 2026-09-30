/**
 * A demo to show using SIGCHLD catch to handle
 * not waited child process termination
 * 
 * test with coomand not using standard input, like "ls"
 * 
 * use of wait macros is exemplified at handle
 */

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "print_utils.h"


void sig_handler(int signum) {
    int child;
    int status;
    while((child = waitpid(-1, &status, WNOHANG)) > 0) {
        safe_printf("child %d terminated with status:\n", child);
    }
    // using of wait macros
    if (WIFEXITED(status)) {
        safe_printf("normal child termination with %d result\n", WEXITSTATUS(status));
    }
    else {
        safe_printf("abnormal(signal) child termination by signal %d\n", WTERMSIG(status)); 
    }
}
 

int main(int argc, char *argv[]) {
    
    signal(SIGCHLD, sig_handler);
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
        signal(SIGINT, SIG_DFL);
        execvp(argv[1], argv+1);
        char err_msg[256];
        sprintf(err_msg, "error execing %s", argv[1]);
        perror(err_msg);
        exit(1);
    }
    // to give time to cmmand termination
    sleep(10);
    printf("check now that the terminated child is not defunct\n");
    printf("press return to continue...");
    getchar();
}
