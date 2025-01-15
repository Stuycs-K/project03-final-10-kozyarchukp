#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <dirent.h>


#ifndef NETWORKING_H
#define NETWORKING_H
#define WKP "mario"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000
#define MAX_CLIENTS 100
#define WIN 2
#define LOSE 1
#define TIE 0
#define FALSE 0
#define TRUE 1
#define TO 0
#define FROM 1
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define NONE -1

#define SYN 0
#define SYN_ACK 1
#define ACK 2
#define MESSAGE 3
#define EXIT 4

int err();

int server_handshake(int *to_client);
int client_handshake(int *to_server);
void server_handshake_half(int *to_client, int from_client);

//for basic & persistent servers
int server_connect(int from_client);

//for forking server
int server_setup();

//multi_server
/*
int multi_server_setup();
int multi_server_connect(int from_client, struct message m);
*/


//from server.c
int new_game();
int server_round();
int winningChoice(int * results);

//from client.c
int join();
struct plr { char name[16]; char password[16]; int wins; int losses; }; //40bytes
struct plr * username();
int client_round(int to_server, int from_server);
int rps(int num_players, int * children[2]);

//from rps
char * input(int bytes);
int one_round(int to, int from);
int won(char * yours, char * opponent);
int isRock(char * str);
int isPaper(char * str);
int isScissors(char * str);
int isRound(char * str);
int isTour(char * str);

#endif
