#include "pipe_networking.h"


int join() {
	int bytes = 0;
	int to_server = 0;
	int from_server = 0;
	int num_rounds = 0;
	int ready = FALSE;
	int result;
	struct plr * player;
	
	printf("welcome to rock paper scissors!\n");
	
	player = username();
	manageUser(player);
	
	
	from_server = client_handshake( &to_server );
	
	bytes = read(from_server, &num_rounds, 4);
		if(bytes!=4)err();
	
	printf("waiting for other players...\n");
	bytes = read(from_server, &ready, 4);
	
	printf("other players connected! game start!\n");
	if (ready){
		for(int i = 0; i<num_rounds; i++){	
			printf("(%d/%d) ", i+1, num_rounds);
			result = client_round(to_server, from_server);
			if(result==TIE){
				printf("it was a tie! one more time..\n");
				i--;
			} else if (result==WIN){
				player->wins++;
				printf("YOU WON!\n");
			} else {
				player->losses++;				
				printf("YOU LOST! :(\n");
			}
		}
		ready = FALSE;
	}
	
	update(player);
}



//executes a round, taking user input, sending it to opponent, processing and returning win
//give it the to_client/to_server file descripters
int client_round(int to_server, int from_server){
	int bytes;
	char * choice = calloc(16, sizeof(char));
	int send;
	int recieved;
	
	
	int valid = FALSE;
	while(!valid){
		printf("type either (r)ock, (p)aper, or (s)cissors: ");
		choice = input(16);	
		if(isRock(choice)){
			valid = TRUE;
			send = ROCK;
		} else if (isPaper(choice)){
			valid = TRUE;
			send = PAPER;			
		} else if(isScissors(choice)){
			valid = TRUE;
			send = SCISSORS;				
		} else { printf("invalid input. ");}
	}
	
	bytes = write(to_server, &send, 4);
		if(bytes!=4)err();
	
	bytes = read(from_server, &recieved, 4);
		if(bytes!=4)err();
	
	if(recieved==-1){
		return TIE;
	} else if(recieved==send){
		return WIN;
	} else {
		return LOSE;
	}
}



