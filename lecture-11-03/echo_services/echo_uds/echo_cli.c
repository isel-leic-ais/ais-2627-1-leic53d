/*
 * implements an echo client using a unix domain stream socket
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>

#include "../utils/chrono.h"
#include "echo_service.h"
 
#define NITERS 1000


#define SHOW_RESP

int read_msg(int sock, echo_msg_t *msg) {
    if (read(sock, &msg->size, sizeof(int)) != sizeof(int)) return -1;
    return read(sock, msg->line, msg->size);
}


int create_client_socket() {
	return socket(AF_UNIX, SOCK_STREAM, 0);
}


int main(int argc, char *argv[]) {
	 
	
	int cli_sock = create_client_socket();
 	
	if (cli_sock < 0) {
		fprintf(stderr, "error creating socket\n");
		return 1;
	}
	
	/* Construct server address, and make the connection */
	struct sockaddr_un srv_address;
	
	memset(&srv_address, 0, sizeof(struct sockaddr_un));
	srv_address.sun_family = AF_UNIX;
	strncpy(srv_address.sun_path, ECHO_SERVICE_NAME, 
			sizeof(srv_address.sun_path) - 1);
	
	if (connect(cli_sock, (struct sockaddr *) &srv_address, 
	          sizeof(struct sockaddr_un)) == -1) {
		fprintf(stderr, "Error connecting socket\n");
		return 2;
	}
	
	echo_msg_t msg, resp;
		
	
	if (argc == 2) {
		while(fgets(msg.line, MAX_MSG_SIZE, stdin)) {
            msg.size = strlen(msg.line)+1;
			write(cli_sock, &msg,  msg_size(msg));
            
			// get response
			read_msg(cli_sock, &resp);
			printf("%s\n", resp.line);
		}
		 
	}
	else {
		int pid  = getpid();

		chrono_t chron = chrono_start();

		for(int try=1; try <= NITERS; try++) {
			sprintf(msg.line, "Hello_%d_%d", pid, try);
            msg.size = strlen(msg.line)+1;
			write(cli_sock, &msg,  msg_size(msg));
			// get response
			read_msg(cli_sock, &resp);
	#ifdef SHOW_RESP
			printf("%s\n", resp.line);
	#endif
		}
		
		printf("%d tries in %ld micros!\n", NITERS, chrono_micros(chron));
		
		printf("press return to continue..."); getchar();
	}
	close(cli_sock);

	printf("client done!\n");
	return 0;
}
