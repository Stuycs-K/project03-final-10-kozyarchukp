#include "pipe_networking.h"


int join() {
	int bytes = 0;
	int to_server = 0;
	int from_server = 0;
	int num_rounds = 0;
	int ready = FALSE;
	struct plr * player;
	
	printf("welcome to rock paper scissors!\n");
	
	player = username();
	
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
				
		}
	}
	
	client_round(to_server);
}

//executes a round, taking user input, sending it to opponent, processing and returning win
//give it the to_client/to_server file descripters
int client_round(int to_server){
	int bytes;
	char * choice = calloc(16, sizeof(char));
	int send;
	
	
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
}

struct plr * username(){
	char * username = calloc(16, sizeof(char));
	int plr_file;	
	int NEW_PLR = FALSE;
	int bytes;
	char *password = calloc(16, sizeof(char));	
	struct plr *player;	
	
	printf("please enter a username (up to 15 chars): ");
	username = input(15);
	
	strcpy(player->name, username);
	
	if(chdir("plr-files")==-1)err();
	
	plr_file = open(username, O_RDWR, 0);
	if(plr_file==-1){
		NEW_PLR = TRUE;
		plr_file = open(username, O_RDWR | O_CREAT, 0666);
		if(plr_file==-1)err();
	}
	
	if(NEW_PLR){
		printf("you are making a new account! please type a password (up to 15 chars): ");
		password = input(16);
		
		strcpy(player->password, password);
		player->wins = 0;
		player->losses = 0;
		
		printf("account succesfully created!\n");
		
		bytes = write(plr_file, player, 40);
		if(bytes!=40)err();
	} else {
		bytes = read(plr_file, player, 40);
		if(bytes!=40)err();
		
		printf("type your password: ");
		password = input(15);
		
		if(strcmp(player->password, password)==0){
			printf("welcome %s!\n", username);
		} else {
			printf("incorrect password. BOO\n");
			exit(0);
		}
	}
	
	if(chdir("..")==-1)err();
	
	return player;
}

