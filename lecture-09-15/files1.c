#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

/**
 * This program opens the same file twice,
 * getting two different file descriptors,
 * and using them to write on the file.
 * 
 * Execute it with and without the comment in line: "#define WITH_DUP"
 * Check the result.
 */
 
 
#define FILENAME "xx.txt"

// to use later
// #define WITH_DUP  

int main() {
	
	int fd;
    
	/// first use open to create the file, if it not exists,
    /// and opening it for writing
	
    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd == -1) {
        perror("error creating file:");
        exit(1);
    }
    
    
    /// write on it
	write(fd, "12345", 5);
    
    
	int fd2;

    /// Now open again the file, this time for rw

#ifndef WITH_DUP
  
    fd2 = open(FILENAME, O_RDWR);
    if (fd2 == -1) {
        perror("error opening file:");
        exit(1);
    }
#else
    /// try duplicate the fd instead of open

    fd2 = dup(fd);
	write(fd2, "6789", 4);
#endif
	
	
    
    
    /// close both file descriptors
    
    close(fd);
    close(fd2);
	return 0;
	
}
