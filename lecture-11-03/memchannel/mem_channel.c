#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "mem_channel.h"
#include "memutils.h"

 
mem_channel_t *mc_create(const char *name) {
 
	mem_channel_t *mc;
	 	
	mc = (mem_channel_t *) shmem_create(name, sizeof(mem_channel_t)); 
	if (mc == NULL) return NULL;
	 
	mc->ownerid = getpid();
	rb_init(&mc->rb);
	return mc;
}

/**
 * Opens an existing channel on shared memory
 */
mem_channel_t *mc_open(const char *name) {	
	return shmem_open(name);
}


/**
 * 
 * Send a request to server
 */
bool mc_put(mem_channel_t *mc, char val) {
	return rb_put(&mc->rb, val);
}

int mc_getall(mem_channel_t *mc, char *packet, int packet_size) {
	// wait for items avaiable
	 
	 
	return rb_getall(&mc->rb, packet, packet_size);
}


void mc_destroy(mem_channel_t *mc, const char *name) {
	if (mc == NULL) return;
	if (mc->ownerid != getpid()) {
		munmap(mc, sizeof(mem_channel_t));
		return;
	}	 
	shmem_destroy(name, mc, sizeof(mem_channel_t));
}
