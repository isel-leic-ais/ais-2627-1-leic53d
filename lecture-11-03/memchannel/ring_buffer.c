#include "ring_buffer.h"
#include <stdio.h>
#include <string.h>


int min(int i1, int i2) {
    return i1 < i2 ? i1 : i2;
}

void rb_init(ring_buffer_t *rb) {
    rb->iput = 0;
    rb->iget = 0;
}

bool rb_put(ring_buffer_t *rb, char val) {
    uint64_t pget = atomic_load(&rb->iget);
    uint64_t iput = atomic_load(&rb->iput);
    // printf("iput=%ld, iget=%ld\n", iput, pget);
    if ((iput - pget) == BUFFER_SIZE) {
      
        return false;
    }

    int pput = iput % BUFFER_SIZE;
     
    rb->buffer[pput] = val;
    atomic_store(&rb->iput, iput + 1);

    return true;
}

int rb_getall(ring_buffer_t *rb, char *packet, int packet_max) {
    uint64_t pput = atomic_load(&rb->iput);
    uint64_t iget = atomic_load(&rb->iget);
    if (iget == pput) { // empty ringbuffer
        return 0;
    }
    
    int size = min(packet_max, pput - iget);
    pput = pput % BUFFER_SIZE;
    int pget = iget % BUFFER_SIZE;
    if (pget + size <= BUFFER_SIZE) {
        // printf("simple copy! (size =%d, pget=%ld,pput=%ld): ", size, pget,pput);
        // show_buffer(rb->buffer, BUFFER_SIZE);
        // printf("\n");
        memcpy(packet, rb->buffer + pget, size);
    }
    else {
        //printf("splitted copy! (size =%d, pget=%d,pput=%ld): ", size, pget,pput);
        //  show_buffer(rb->buffer, BUFFER_SIZE);
        //  printf("\n");
         memcpy(packet, rb->buffer + pget, BUFFER_SIZE - pget);
         memcpy(packet + BUFFER_SIZE - pget, rb->buffer, size - (BUFFER_SIZE - pget));
    }
    //atomic_fetch_add(&rb->iget, size);
    atomic_store(&rb->iget, iget + size);
     
    return size;
}
