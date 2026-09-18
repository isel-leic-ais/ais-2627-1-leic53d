#define PERROR2
#define WITH_PARENT_PAUSE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#ifdef PERROR2
#include <stdarg.h>
#endif
 


#ifdef PERROR2
void perror2(const char *format, ...) {
    char msg[256];
    va_list argList;
	
    va_start(argList, format);
    vsnprintf(msg, 256, format, argList);
    va_end(argList);
    perror(msg);
}
#endif

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("sintax: launch cmd args...\n");
        exit(1);
    }

    pid_t child = fork();
    if (child == -1) {
        perror("error forking child");
        exit(1);
    }
    else if (child == 0) {
        // child code
        // execv prefixed functions receive an array that will be
        // copied to the argv passed to the new main 
        // (that is, new argv layout can be defined at execution time)
        //
        // execl prefixed functions receive a variable number of arguments
        // that will be used to create the argv passed to the new main
        // (that is, new argv layout is defined at compilation time)
        //
        // execvp and execlp search executable file names on folders
        // refered by path
        // execl and execv need absolute execute file names
        // 
        if (execvp(argv[1], argv+1) == -1) {
#ifndef PERROR2
            char err_msg[256];
            sprintf(err_msg, "error execing %s", argv[1]);
            perror(err_msg);
#else
            perror2("error execing %s", argv[1]);
#endif
        }
        exit(1);
    }
    else {
        // parent code
#ifdef WAITPID
        waitpid(child, NULL, 0);    
#endif
#ifdef WITH_PARENT_PAUSE
        // define WITH_PARENT_PAUSE
        // to check the state of child process after exit
        // use a cmd that not use standard input (eg: ls)
        sleep(1);
        printf("press return to continue...");
        getchar();
#endif 
    }
    
  
    return 0;
}
