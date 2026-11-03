#pragma once

#define CHANNEL_NAME_MAX_SIZE 256

#define ECHO_DIR		  "/tmp/"
#define ECHO_SERVICE_NAME ECHO_DIR "echo_fifo_service"

#define ECHO_CLIENT_PREFIX  ECHO_DIR "client_"
#define MAX_MSG_SIZE 256

typedef struct msg_header {
    int msg_size;
	int sender;
} msg_header_t;

typedef struct  {
    msg_header_t header;
	char line[MAX_MSG_SIZE];
} echo_msg_t;

#define msg_size(m) ( (m).header.msg_size + sizeof(msg_header_t))

