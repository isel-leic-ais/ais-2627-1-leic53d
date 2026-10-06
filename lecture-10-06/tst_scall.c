#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "chrono.h"

/**
 * this program tests the implementation
 * of our version of system call getpid using old "int" method (my_getpid)
 * versus the library implementation using "syscall"
 */

 
int mygetpid_32();

#define NTRIES 100000
 

#define NanosPerCall(micros, ncalls)  ((micros*1000)/ ncalls)

int main()
{

	int pid1, pid2;

	chrono_t chrono = chrono_start();
	for (int i = 0; i < NTRIES; ++i) {
		pid1 = mygetpid_32();
	}
	long micros = chrono_micros(chrono);
	printf("with my_getpid in %ld micros (%ld nanos per call)\n", 
		micros, NanosPerCall(micros, NTRIES));

	chrono = chrono_start();
	for (int i = 0; i < NTRIES; ++i) {
		pid2 = getpid();
	}
	micros = chrono_micros(chrono);
	printf("with getpid in %ld micros (%ld nanos per call)\n",
		 micros, NanosPerCall(micros, NTRIES));

	printf("pid with my_getpid is %d\n", pid1);
	printf("pid with getpid is %d\n", pid2);

	return 0;
}
