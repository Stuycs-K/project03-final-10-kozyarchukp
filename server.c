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

	int bytes = 0;
	int num_rounds;	
	int num_players;
	char * gamemode = calloc(16, sizeof(char));
	
	printf("welcome to rock paper scissors!\n");
	/*
	printf("choose a gamemode ((r)ounds, or (t)ournament)\n");
	gamemode = input(16);
	
	if(isRound(gamemode)){
		server_round();
	}
	*/
	server_round();

	
}

int server_round(){
	int num_players;
	int num_rounds;
	int bytes;
	char * buff = calloc(2, sizeof(char));	
	
	
	printf("how many players?\n");
	buff = input(4);
	sscanf(buff, "%d", &num_players);
	printf("how many rounds (up to 99) would you like to play? ");
	buff = calloc(2, sizeof(char));
	buff = input(4);
	sscanf(buff, "%d", &num_rounds);
	
	int ** children = calloc(num_players*2, sizeof(int));
	for(int i = 0; i < num_players; i++){
		children[i] = calloc(2, sizeof(int));
		printf("waiting for player %d...\n", i+1);
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
	
	for (int i = 0; i < num_rounds; i++){
		int result = rps(num_players, children);
		if (result==NONE){
			i--;
		}
	}
}


int rps(int num_players, int ** children){
	int results[num_players]; //holds the corresponding results
	int bytes;
	int winner;
	
	for(int i=0; i<num_players; i++){
		bytes = read(children[i][FROM], &results[i], 4);
			if(bytes!=4)err();
	}
	
	winner = winningChoice(results, num_players);
	
	for(int i = 0; i<num_players; i++){
		bytes = write(children[i][TO], &winner, 4);
			if(bytes!=4)err();
	}
	
	return winner;
}


//returns either ROCK, PAPER, SCISSORS, or NONE based off which one won
int winningChoice(int * results, int num_players){
	int num_rocks = 0;
	int num_papers = 0;
	int num_scissors = 0;
	
	for(int i = 0; i<num_players;i++){
		if(results[i]==ROCK){
			num_rocks++;
		} else if (results[i]=PAPER){
			num_papers++;
		} else if (results[i]=SCISSORS){
			num_scissors++;
		} 
	}
	/*
	printf("num_rocks: %d\n", num_rocks);
	printf("num_papers: %d\n", num_papers);
	printf("num_scissors: %d\n", num_scissors);
	*/
	if (num_rocks>0 && num_papers>0 && num_scissors>0){
		return NONE;
	} else if (num_rocks>0 && num_papers>0){
		return PAPER;
	} else if (num_rocks>0 && num_scissors>0){
		return ROCK;
	} else if (num_papers>0 && num_scissors>0){
		return SCISSORS;
	} else {
		return NONE;
	}
	
	/*if (results[0] == ROCK){
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
	*/
}




