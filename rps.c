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
	//printf("calloced space, starting fgets\n");
	fgets(input_buffer, bytes-1, stdin);
	//cut input_buffers at the \n 
	input_buffer = strsep( &input_buffer, "\n");	
	return input_buffer;
}

//executes a round, taking user input, sending it to opponent, processing and returning win
//give it the to_client/to_server file descripters
int one_round(int to, int from){
	int bytes;
	
	printf("type either (r)ock, (p)aper, or (s)cissors: ");
	char * choice = calloc(16, sizeof(char));
	choice = input(16);	
	printf("\nyour choice is %s\n", choice);
	/*
	bytes = write(to, choice, 16);
		if(bytes!=16)err();
	
	char * response = calloc(16, sizeof(char));
	bytes = read(from, response, 16);
		if(bytes!=16)err();
	
	printf("recieved %s from opponent\n", response);
	*/
}

