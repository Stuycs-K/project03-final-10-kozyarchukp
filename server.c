#include "pipe_networking.h"

void sighandler(int signo){
	if(signo == SIGINT){
		remove(WKP);
		exit(0);
	}

}

int new_game() {
	signal(SIGINT, sighandler);
	signal(SIGPIPE, SIG_IGN);
	
	int to_client = 0;
	int from_client = 0;
	int bytes = 0;
	pid_t pid;
	
	printf("welcome to rock paper scissors!\n");
	//ask for how many players. for now, assume 1.
	int num_players = 1;
	printf("waiting for player 2...\n");
	from_client = server_setup();
	//pid = fork();
	//if(pid==0){
		//child
	server_handshake_half(&to_client, from_client);
	printf("player 2 connected!\n");	

	one_round(to_client, from_client);
	//} 
	
	close(to_client);
	close(from_client);
	
}

