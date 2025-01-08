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
	//pid_t pid;
	int num_rounds;	
	
	printf("welcome to rock paper scissors!\n");
	printf("how many rounds (up to 99) would you like to play? ");
	char * buff = calloc(2, sizeof(char));
	buff = input(4);
	sscanf(buff, "%d", &num_rounds);
		
	printf("waiting for player 2...\n");
	from_client = server_setup();
	//pid = fork();
	//if(pid==0){
		//child
	server_handshake_half(&to_client, from_client);
	printf("player 2 connected!\n");	
	
	bytes = write(to_client, &num_rounds, 4);
		if(bytes!=4)err();	
	
	for(int i = 0; i<num_rounds; i++){
		one_round(to_client, from_client);
	}
	
	close(to_client);
	close(from_client);
	
}

