/**
 * Execute the program as is and observe the results
 * Uncommente line "fflush(stdout)
 * and try to explain the differences
 */

#include <stdio.h>
#include <unistd.h>

int main() {
    // mix fd and FILE output
    
    //FILE* 
   
    // use standard output via FILE*
    fputs("First", stdout);
    
    
    //fflush(stdout);

    // use standard output via fd
    write(STDOUT_FILENO /* 1 */, "Second\n", 7);

    // show fd associated to stdout FILE*
    
    int fd_out = fileno(stdout);
    printf("fd_out=%d\n", fd_out);

    return 0;
}
