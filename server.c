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
	

	int pipe[2];
	int bytes = 0;
	//pid_t pid;
	int num_rounds;	
	
	printf("welcome to rock paper scissors!\n");
	printf("how many rounds (up to 99) would you like to play? ");
	char * buff = calloc(2, sizeof(char));
	buff = input(4);
	sscanf(buff, "%d", &num_rounds);
		
	printf("waiting for player 2...\n");
	pipe[FROM] = server_setup();
	//pid = fork();
	//if(pid==0){
		//child
	server_handshake_half(&pipe[TO], pipe[FROM]);
	printf("player 2 connected!\n");	
	
	bytes = write(pipe[TO], &num_rounds, 4);
		if(bytes!=4)err();	
	
	for(int i = 0; i<num_rounds; i++){
		printf("(%d/%d)", i+1, num_rounds);
		one_round(pipe[TO], pipe[FROM]);
	}
	
	close(pipe[TO]);
	close(pipe[FROM]);	
}

