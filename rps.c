#include "pipe_networking.h"

int main(){
	char *user_input;
	int num_players;
	int num_rounds;
	
	printf("type 'new' to create a new game server. type 'join' to join the game server.\n");

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
		if(strcasecmp(str, "sciscors")==0){
			printf("HAHAHAH YOU SPELLED IT WRONG\n");
		}
		return TRUE;
	} else return FALSE;
}

int isRound(char * str){
	if (strcasecmp(str, "rounds")== 0 || strcasecmp(str, "r")==0) {
		return TRUE;
	} else return FALSE;	
}

int isTour(char * str){
	if (strcasecmp(str, "tournament")== 0 || strcasecmp(str, "t")==0) {
		return TRUE;
	} else return FALSE;	
}


