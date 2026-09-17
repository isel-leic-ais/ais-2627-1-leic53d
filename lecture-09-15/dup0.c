#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


#define OUT_FILE "out.txt"

/**
 * this program just show the use of "dup2" system call
 * that copies the file descritor "fd" to file descriptor "1"
 * closing the last descriptor if it is not closed (avaiable)
 * 
 * the "dup" system call receive just on file descritor, and copies it
 * to the first avaiable descriptor on process descriptor table.
 * 
 */
 
int main() {
	
    // open a file and redirect it to standard output
    
	int fd;
    
	
    fd = open(OUT_FILE, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        perror("error creating redirection file");
        exit(1);
    }
	
    printf("fd = %d\n", fd);
    
    close(STDOUT_FILENO);
    
	int newfd;
    
    // duplicate fd into newfd  
    
    newfd= dup(fd);
    
    close(fd);
    
   
	
	printf("newfd = %d\n", newfd);
    
	printf("Hello, World redirected!\n");
	
	return 0;
	
}
