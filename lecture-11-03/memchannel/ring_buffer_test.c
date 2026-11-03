#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"
#include "ring_buffer.h"
#include "chrono.h"

#define TOTAL_LETTERS (1024*1024)




void *fun_writer(void *arg) {
    ring_buffer_t *rb = (ring_buffer_t *) arg;
    int send = 0;
    char curr = 'A';
    while (send < TOTAL_LETTERS) {
        if (rb_put(rb, curr)) {
            send++;
            curr++;
            if (curr > 'Z') {
                curr = 'A';
            }
        }
        else {
            //printf("rb_put fail at %d\n", send);
        }
      
    }
    //printf("writer terminated!\n");
    return NULL;

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

void *fun_reader(void *arg) {
    ring_buffer_t *rb = (ring_buffer_t *) arg;
    int received = 0;
    char packet[BUFFER_SIZE];
    char last_letter = 'A' - 1;
    int steps = 1;
    while(received < TOTAL_LETTERS) {
        int nletters = rb_getall(rb, packet, 100 );
        if (nletters > 0) {
            // printf("received=%d, last_letter=%c: ", received, last_letter);
            // show_buffer(packet, nletters);
            // printf("\n");
            assert_buffer(packet, nletters, last_letter);
            last_letter = packet[nletters-1];
            received += nletters;
           
            if (received >= 100000*steps) {
                printf("%d\r", received);
                steps++;
                fflush(stdout);
            }
          
        }
        else {
            sleep(0);
        }
    }
    //printf("received terminated!\n");
    return NULL;

}


int main() {
    ring_buffer_t rb;

    chrono_t chrono = chrono_start();

    rb_init(&rb);

    pthread_t reader, writer;
    pthread_create(&reader, NULL, fun_reader, &rb);
    pthread_create(&writer, NULL, fun_writer, &rb);

    pthread_join(reader, NULL);
    pthread_join(writer, NULL);

    printf("successfull test in %ld ms!\n", chrono_micros(chrono)/1000);
    return 0;
}
