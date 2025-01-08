#include "pipe_networking.h"


int join() {
	int bytes = 0;
	int to_server = 0;
	int from_server = 0;
	
	printf("connecting to server...\n");
	from_server = client_handshake( &to_server );
	printf("successfully connected to server!\n");
	
	one_round(to_server, from_server);	
}

