#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "chrono.h"
#include <errno.h>

/**
 * this program tests the implementation
 * of our old int version of system call write (my_write)
 */

int mywrite_32(int fd, const void *buf, int size);
 
char msg[] = "hello again!\n";

int  main() {
	
	printf("message address = %p\n", msg);
	int res = mywrite_32(STDOUT_FILENO, msg, 13);
	if (res <0) {
		errno = -res;
		res = -1;
		perror("write error");
		return 1;
	} 
	printf("%d bytes written\n", res);
	return 0;
}