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
	

	//int pipe[2];
	int bytes = 0;
	//pid_t pid;
	int num_rounds;	
	int num_players;
	char * gamemode = calloc(16, sizeof(char));
	
	printf("welcome to rock paper scissors!\n");
	printf("choose a gamemode ((r)ounds, or (t)ournament)\n");
	gamemode = input(16);
	
	if(isRound(gamemode)){
		server_round();
	}
	

	
		/*
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
	*/
	
	//######## MAKE SURE TO CLOSE THE PIPES LATE RIM TO LAZY RN ##########
	//close(children[nu[TO]);
	//close(pipe[FROM]);	
}

int server_round(){
	int num_players;
	int num_rounds;
	int bytes;
	
	printf("how many players?\n");
	char * buff = calloc(2, sizeof(char));
	buff = input(4);
	sscanf(buff, "%d", &num_players);
	printf("recieved %d\n", num_players);
	printf("how many rounds (up to 99) would you like to play? ");
	buff = calloc(2, sizeof(char));
	buff = input(4);
	sscanf(buff, "%d", &num_rounds);	

	int children[num_players][2];
	for(int i = 0; i < num_players; i++){
		printf("waiting for player %d...\n", i+1);
		int from_client;
		int to_client;
		children[i][FROM] = server_handshake(&children[i][TO]);
		printf("player %d connected!\n", i+1);	
		
		//write number of rounds
		bytes = write(children[i][TO], &num_rounds, 4);
			if(bytes!=4){
				printf("issue whe writing number of rounds to child\n");
				err();
			}					
	}			
	//all players are connected, give the signal to start!
	for(int i = 0; i < num_players; i++){
		int ready = TRUE;
		bytes = write(children[i][TO], &ready, 4);
	}
	
	
	
}

//
int rps(int num_players, int**children){
	int children[num_players][2]; //holds the fds
	int results[num_players]; //holds the corresponding results
	int bytes;
	int winner;
	
	for(int i=0; i<num_players; i++){
		bytes = read(children[i][FROM], results[i], 4);
	}
	
	
	if(num_players==2){
		int winner = winningChoice(results);
	}
	
	//3 rocks, 2 paper
	/*
		two player:
			normal rules
		else...
	count how many rocks, papers and scissors were thrown
		will be a TIE if two are 0, or NONE are 0.
		if one is equal to 0, NOT TIE!
			if (num_rock>0 && num_paper>0){
				paper win
			} else if (num_rock>0 && num_scissors>0){
				rock win
			} else if (num_paper>0 && num_scissors>0){
				scissors win
			} 
	*/
		
	}
}

//returns 1 if you lose, 2 if you won, 0 if a tie, -1 if invalid input
int winningChoice(int * results){
	if (results[0] == ROCK)){
		if(results[1] == ROCK){
			return NONE;
		} else if (results[1] == SCISSORS){
			return ROCK;			
		} else if (results[1] == PAPER){
			return PAPER;			
		}
	} else if (results[0] == SCISSORS){
		if(results[1] == ROCK){
			return ROCK;
		} else if (results[1] == SCISSORS){
			return NONE;			
		} else if (results[1] == PAPER){
			return SCISSORS;			
		}
	} else if (results[0] == PAPER){
		if(results[1] == ROCK){
			return PAPER;
		} else if (results[1] == SCISSORS){
			return SCISSORS;			
		} else if (results[1] == PAPER){
			return NONE;
		}
	} else {
		printf("invalid input");
		return -1;
	}
}




