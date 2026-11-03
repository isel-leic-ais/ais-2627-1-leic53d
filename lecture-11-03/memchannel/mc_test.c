#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <time.h>
#include "../utils/utils.h"
#include "mem_channel.h"
#include <semaphore.h>
#include "../utils/chrono.h"

#define TOTAL_LETTERS (1024*1024)

#define CHANNEL_NAME "mem_channel"

sem_t *start;

sem_t *create_shared_sem() {
    sem_t *aux = (sem_t*) mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(aux, 1, 0);
    return aux;
}

void fun_writer() {
    printf("entering writer!\n");
    mem_channel_t *mc = mc_create(CHANNEL_NAME);
    int send = 0;
    char curr = 'A';
    sem_post(start);
    printf("start writer!\n");
    while (send < TOTAL_LETTERS) {
        if (mc_put(mc, curr)) {
            send++;
            curr++;
            if (curr > 'Z') {
                curr = 'A';
            }
        }
        else {
          // printf("rb_put fail at %d\n", send);
          sleep(0);
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

void fun_reader() {
    printf("entering reader!\n");
    sem_wait(start);
    mem_channel_t *mc = mc_open(CHANNEL_NAME);
    if (mc == NULL) {
        failure("non existent shared memory!");
    }
    int received = 0;
    char packet[BUFFER_SIZE];
    char last_letter = 'A' - 1;
    printf("start reader!\n");
    while(received < TOTAL_LETTERS) {
        int nletters = mc_getall(mc, packet, BUFFER_SIZE );
        if (nletters > 0) {
           // printf("nletters=%d\n", nletters);
           // printf("received=%d, letter =%c, last_letter=%c\n", received, packet[0], last_letter);
            // show_buffer(packet, nletters);
            // printf("\n");
            received += nletters;
         
          
            assert_buffer(packet, nletters, last_letter);
           
            last_letter = packet[nletters-1];
           
            if (received % 10000 == 0) {
                printf("%d\r", received);
            }
            fflush(stdout);
            
         
        }
        else {
            //printf("sleep\n");
            sleep(0);
        }
    }
  
    printf("received terminated!\n");
}


int main() {

    shm_unlink(CHANNEL_NAME);
  
    start = create_shared_sem();

    pid_t writer_child, reader_child;

    if ((writer_child = fork()) == 0) {
        fun_writer();
        exit(0);
    }
    
    
    if ((reader_child = fork()) == 0) {
        fun_reader();
        exit(0);
    }
    chrono_t chrono = chrono_start();

    int writer_status, reader_status;

    waitpid(writer_child, &writer_status, 0);
    waitpid(reader_child, &reader_status, 0);
    printf("successfull test in %ld ms!\n", chrono_micros(chrono)/1000);
    return 0;
}
