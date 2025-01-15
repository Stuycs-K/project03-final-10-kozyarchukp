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
	while(!ready){
		printf("type 'stats' to check your win/loss ratio, 'change pwd' to change your password, 'delete' to delete your account, or 'start' to start the game.\n");
		char * buff = calloc(16, sizeof(char));
		buff = input(10);
		
		if(strcmp(buff, "stats")==0){
			printf("wins: %d\n", player->wins);
			printf("losses: %d\n", player->losses);
		} else if (strcmp(buff, "change pwd")==0){
			printf("choose a new password (up to 15 chars): ");
			buff = input(15);
			strcpy(player->password, buff);
			update(player);
		} else if (strcmp(buff, "delete")==0){
			remove(player->name);
			exit(0);
		} else if (strcmp(buff, "start")==0){
			break;
		}
	}
	ready = FALSE;
	
	
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

int update(struct plr * player){
	int bytes;
	int plr_file = open(player->name, O_WRONLY | O_TRUNC, 0);
	bytes = write(plr_file, player, 40);
		if(bytes!=40)err();
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

