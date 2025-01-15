#include "pipe_networking.h"

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

int update(struct plr * player){
	int bytes;
	chdir("plr-files");
	printf("going to try to open file %s\n", player->name);
	int plr_file = open(player->name, O_WRONLY | O_TRUNC, 0);
		if(plr_file==-1)err();
	bytes = write(plr_file, player, 40);
		if(bytes!=40)err();
}

int manageUser(struct plr * player){
	printf("type 'stats' to check your win/loss ratio, 'pwd' to change your password, 'delete' to delete your account, or 'start' to start the game.\n");
		char * buff = calloc(16, sizeof(char));
		buff = input(10);
		
		if(strcmp(buff, "stats")==0){
			printf("wins: %d\n", player->wins);
			printf("losses: %d\n", player->losses);
			manageUser(player);
		} else if (strcmp(buff, "pwd")==0){
			printf("choose a new password (up to 15 chars): ");
			buff = input(15);
			strcpy(player->password, buff);
			printf("updated player->password to be %s\n", player->password);
			update(player);
			printf("updated the file!\n");
			manageUser(player);			
		} else if (strcmp(buff, "delete")==0){
			remove(player->name);
			exit(0);
		} else if (strcmp(buff, "start")==0){
			return 0;
	}	
}