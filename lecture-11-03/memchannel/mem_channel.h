#pragma once

#include <sys/types.h>

#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include "ring_buffer.h"

#define CHANNEL_NAME_MAX_SIZE 	 32
#define MAX_MSG			  	    512

typedef unsigned char byte;

typedef struct {
	pid_t ownerid;			    // the creator process
    ring_buffer_t rb;			// shared the char buffer
} mem_channel_t;



/**
 * Create a single channel on shared memory
 */
mem_channel_t *mc_create(const char *name);
	 

/**
 * Opens a single channel on shared memory
 */
mem_channel_t *mc_open(const char *name);
	 
// client operations
bool mc_put(mem_channel_t *mc, char val);
int mc_getall(mem_channel_t *mc, char *packet, int size);
void mc_destroy(mem_channel_t *rb, const char *name);
 
