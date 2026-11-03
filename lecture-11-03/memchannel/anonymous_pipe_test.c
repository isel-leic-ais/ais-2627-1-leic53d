#include <stdio.h>

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "chrono.h"
#include "utils.h"


#define TOTAL_LETTERS (1024*1024)
#define PACKET_SIZE 1024

int channel[2];


int pipe_put(char val) {
    write(channel[1], &val, 1);
    return true;
}

int pipe_getall(char *str, int capacity) {
    return read(channel[0], str, capacity);
}

void writer() {
     
    int send = 0;
    char curr = 'A';
    while (send < TOTAL_LETTERS) {
        if (pipe_put(curr)) {
            send++;
            curr++;
            if (curr > 'Z') {
                curr = 'A';
            }
        }
    }
    printf("writer terminated!\n");
}

void assert_buffer(char buffer[], int size, char last_letter) {

    if (buffer[0] != (last_letter+1) && (last_letter == 'Z' && buffer[0] != 'A')) {
        failure("assertion rb[i](%c) == (rb[i-1]+1)(%c) violated at %d!",
                   buffer[0], last_letter, 0);
    }
    for(int i=1; i < size; ++i) {
        if (buffer[i] != buffer[i-1]+1 && (buffer[i-1] == 'Z' && buffer[i] != 'A')) {
            failure("assertion rb[i](%c) == (rb[i-1]+1)(%c) violated at %d!",
                   buffer[i], buffer[i-1], i);
            
        }
    }
}

void reader() {
    int received = 0;
   
    char packet[PACKET_SIZE];
    char last_letter = 'A' - 1;

    while(received < TOTAL_LETTERS) {
        int nletters = pipe_getall(packet, PACKET_SIZE );
        if (nletters > 0) {
            // printf("received=%d, last_letter=%c: ", received, last_letter);
            // show_buffer(packet, nletters);
            // printf("\n");
            assert_buffer(packet, nletters, last_letter);
            last_letter = packet[nletters-1];
            received += nletters;
            if (received % 10000 == 0) {
                printf("%d\r", received);
            }
            fflush(stdout);
           
        }
        else {
            //sleep(0)
        }
    }
    printf("received terminated!\n");
}

int main() {
    chrono_t chrono = chrono_start();

    pipe(channel);
    
    int pid = fork();

    if (pid == 0) { // child
        writer();
        exit(0);
    }
    reader();
    printf("successfull test in %ld ms!\n", chrono_micros(chrono)/1000);
    return 0;
}
