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
	int gamemode;
	
	userInput(&num_players, &num_rounds, &gamemode);
	
	if(gamemode==ROUNDS){
		server_round(num_players, num_rounds);
	} else if (gamemode==BESTOF){
		
	}
}



int server_bestof(int num_players, int num_rounds){
	int bytes;
	char * buff = calloc(2, sizeof(char));	
	
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

int server_round(int num_players, int num_rounds){
	int bytes;
	char * buff = calloc(2, sizeof(char));	
	
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

//returns which choice won ROCK PAPER SCISSORS or NONE, and sends it to the child
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
		} else if (results[i]==PAPER){
			num_papers++;
		} else if (results[i]==SCISSORS){
			num_scissors++;
		} 
	}
	
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
}

int userInput(int * num_players, int * num_rounds, int * gamemode){
	char * buff = calloc(16, sizeof(char));
	printf("choose a gamemode ('(r)ounds', or '(best) of')\n");
	buff = input(15);
	if(isRounds(buff)){
		*gamemode = ROUNDS;
	} else if (isBest(buff)){
		*gamemode = BESTOF;
	} else {
		printf("invalid input\n");
		exit(1);
	}
	
	if(*gamemode==ROUNDS){
		printf("how many players?\n");
		buff = input(4);
		sscanf(buff, "%d", num_players);

		printf("how many rounds (up to 99) would you like to play? ");
		buff = calloc(2, sizeof(char));
		buff = input(4);
		sscanf(buff, "%d", num_rounds);			
	}
	
	else if (*gamemode==BESTOF){
		*num_players = 2;
		
		printf("best of how many rounds? ");
		buff = calloc(2, sizeof(char));
		buff = input(4);
		sscanf(buff, "%d", num_rounds);		
		if(*num_rounds%2==0){
			printf("must be an odd number.\n");
		}
	}
}





