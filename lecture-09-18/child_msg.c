
// try comment next define and explain the efect
#define CLOSE_PIPE_OUT

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>


int main() {
    
    int p[2];

    if (pipe(p) == -1) {
        perror("error creating pipe");
        exit(1);
    }

    pid_t child= fork();
    char msg[128] = "empty";
    
    if (child == -1) {
        perror("error creating child");
        exit(1);
    }
    else if (child == 0) {
        // child code
        close(p[0]);
        printf("on child, msg= '%s'\n", msg);
        char *child_msg = "Hello from child!";
        write(p[1], child_msg, strlen(child_msg)+1);
        exit(0);
    }
    else {
#ifdef CLOSE_PIPE_OUT
        close(p[1]);
#endif
        int total =0, nr;
        while((nr = read(p[0], msg + total, 128)) != 0) {
            total += nr;
        };
        waitpid(child, NULL, 0);
        printf("on parent, msg= '%s'\n", msg);

    }
    return 0;
}