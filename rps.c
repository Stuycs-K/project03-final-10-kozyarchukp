#include "pipe_networking.h"

/*
	run main
		"welcome to rps!"
		run username
			"please enter a username:"
			after processing the username, go into the player-files folder.
			search for a .plr file with the same name as the username. 
				if exists:
					"welcome back /username/!"
					"please enter your password:"
					make sure it matches with the first 17 bytes in the character file.
						if it matches, finish.
						if it doesnt match
							"wrong password."
							run username again
				if it doesn't:
					"welcome /username/!"
					create a new file in the player-files folder named /username/.plr
					"please enter a password (up to 16 chars)"
						save the password as the first 17 bytes in /username/.plr
					finish
	"succesfully logged in. to check your stats, type stats. to check leaderboard,
	type leaderboard. to start a new game, type 'new'. to join an existing game,
	type 'join' (make sure a game exists first)
	
	while loop that takes user input and runs corresponding function
	if new:
		run new()
			
*/


int main(){
	char *user_input;
	int num_players;
	int num_rounds;
	
	printf("type 'new' to create a new game. type 'join' to join an existing game.\n");

	user_input = input(16);
	
	//printf("%d\n", strcmp(user_input, "new"));
	if(strcmp(user_input, "new")==0){
		new_game();
	} else if (strcmp(user_input, "join")==0){
		join();
	} else { printf("invalid input\n"); }
	
}


//takes up to bytes input from stdin. cuts the string at the newline.
char * input(int bytes){
	char * input_buffer = calloc(bytes, sizeof(char));
	//printf("supposed to wait here i thouhgt?\n");
	fgets(input_buffer, bytes-1, stdin);
	//cut input_buffers at the \n 
	input_buffer = strsep( &input_buffer, "\n");	
	return input_buffer;
}

//executes a round, taking user input, sending it to opponent, processing and returning win
//give it the to_client/to_server file descripters
int one_round(int to, int from){
	int bytes;
	char * choice = calloc(16, sizeof(char));
	
	
	int valid = FALSE;
	while(!valid){
		printf("type either (r)ock, (p)aper, or (s)cissors: ");
		choice = input(16);	
		if(isRock(choice)||isPaper(choice)||isScissors(choice)){
			valid = TRUE;
		} else { printf("invalid input. ");}
	}
	
	bytes = write(to, choice, 16);
		if(bytes!=16)err();
	
	char * response = calloc(16, sizeof(char));
	bytes = read(from, response, 16);
		if(bytes!=16)err();
	
	
	won(choice, response);
}

//returns 1 if you lose, 2 if you won, 0 if a tie, -1 if invalid input
int won(char * yours, char * opponent){
	if (isRock(yours)){
		if(isRock(opponent)){
			printf("it was a tie!\n");
			return TIE;
		} else if (isPaper(opponent)){
			printf("you lose!\n");
			return LOSE;			
		} else if (isScissors(opponent)){
			printf("you win!\n");
			return WIN;			
		}
	} else if (isPaper(yours)){
		if(isRock(opponent)){
			printf("you win!\n");	
			return WIN;
		} else if (isPaper(opponent)){
			printf("it was a tie!\n");	
			return TIE;			
		} else if (isScissors(opponent)){
			printf("you lose!\n");	
			return LOSE;			
		}
	} else if (isScissors(yours)){
		if(isRock(opponent)){
			printf("you lose!\n");	
			return LOSE;
		} else if (isPaper(opponent)){
			printf("you win!\n");	
			return WIN;			
		} else if (isScissors(opponent)){
			printf("it was a tie!\n");		
			return TIE;
		}
	} else {
		printf("invalid input");
		return -1;
	}
}

int isRock(char * str){
	//printf("choice is %s\n", str);	
	if (strcasecmp(str, "rock")== 0 || strcasecmp(str, "r")==0) {
		if(strcasecmp(str, "rokc")==0){printf("HAHAHAH YOU SPELLED IT WRONG\n");}
		return TRUE;
	} else return FALSE;
}

int isPaper(char * str){
	//printf("choice is %s\n", str);	
	if (strcasecmp(str, "paper")== 0 || strcasecmp(str, "p")==0) {
		if(strcasecmp(str, "paepr")==0){printf("HAHAHAH YOU SPELLED IT WRONG\n");}
		return TRUE;
	} else return FALSE;
}

int isScissors(char * str){
	//printf("choice is %s\n", str);
	if (strcasecmp(str, "scissors")== 0 || strcasecmp(str, "s")==0) {
		if(strcasecmp(str, "sciscors")==0){printf("HAHAHAH YOU SPELLED IT WRONG\n");}
		return TRUE;
	} else return FALSE;
}


