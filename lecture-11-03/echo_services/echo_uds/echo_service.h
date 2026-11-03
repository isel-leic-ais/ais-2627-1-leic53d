#pragma once

 
#define ECHO_DIR	"/tmp/"
#define ECHO_SERVICE_NAME ECHO_DIR "echo_unixsock_service"

#define MAX_MSG_SIZE 256


typedef struct  {
    int size;
	char line[MAX_MSG_SIZE];
} echo_msg_t;

#define msg_size(m) ( (m).size + sizeof(int))

 
