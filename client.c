#include "pipe_networking.h"


int join() {
	int bytes = 0;
	int to_server = 0;
	int from_server = 0;
	int num_rounds = 0;
	int ready = FALSE;
	
	printf("connecting to server...\n");
	from_server = client_handshake( &to_server );
	printf("successfully connected to server!\n");
	
	bytes = read(from_server, &num_rounds, 4);
		if(bytes!=4)err();
	
	printf("waiting for other players...\n");
	bytes = read(from_server, &ready, 4);
	
	printf("other players connected! game start!\n");
	if (ready){
		for(int i = 0; i<num_rounds; i++){	
			printf("(%d/%d) ", i+1, num_rounds);
			one_round(to_server, from_server);	
		}
	}
}

