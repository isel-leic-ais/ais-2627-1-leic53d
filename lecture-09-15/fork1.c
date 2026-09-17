#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * In order to distinguish parent from chils executions,
 * fork return different values to both:
 * To the parent is returned the child process id (pid) 
 * and to the child is returned 0 (not a valid id)
 * 
 * The code below show this
 * 
 * Uncomment the  DELAYED_WAIT define and note (using command "ps -ax")
 * that lists all the existing processes,
 * that the child process remains (with state Defunct) while parent is suspended
 * 
 */

//#define DELAYED_WRITE
//#define WITH_WAIT


int main() {
    
    printf("Main: my pid is = %d\n", getpid());
	pid_t child_pid;
	
	child_pid = fork();
	
	if (child_pid == -1) {
		perror("error on fork");
		exit(1);
	}
	else if (child_pid == 0) {
		// on child
		printf("Child: my pid is %d\n", getpid());
#ifdef DELAYED_WRITE
        sleep(5);
#endif
		printf("Child: my parent pid is %d\n", getppid());
        exit(0);
	}
	else {
		// on parent
		printf("Main:process %d created!\n", child_pid);
        // do something simulation
        sleep(2);
#ifdef WITH_WAIT

        int status;
        waitpid(child_pid, &status, 0);
        
        //wait(NULL);
#endif
	}

	return 0; 
}
