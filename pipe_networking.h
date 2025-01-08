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

#ifndef NETWORKING_H
#define NETWORKING_H
#define WKP "mario"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000
#define MAX_CLIENTS 100

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

//from client.c
int join();

//from rps
char * input(int bytes);
int one_round(int to, int from);


#endif
