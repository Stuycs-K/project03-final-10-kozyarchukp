#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
	// 1 server making wkp
	mkfifo(WKP, 0666);
	// 2 server opening wkp (BLOCKS)
	int from_client = open(WKP, O_RDONLY, 0);
	
	//4 remove wkp
	remove(WKP);
	return from_client;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
	int bytes;
	int from_client = server_setup();
	
	//5 Server reading SYN (pp?)
	char PP[8];
	bytes = read(from_client, PP, 8);
	if(bytes==-1)err();
	
	//6 Server opening the Private Pipe [Unblock client]	
	*to_client = open(PP, O_WRONLY, 0);
	
	//7 Server sending SYN_ACK	
	srand(time(NULL));
	int synack = rand();
	bytes = write(*to_client, &synack, 4);
	if(bytes==-1)err();
	
	//9 Server reading final ACK
	int ack;
	bytes = read(from_client, &ack, 4);
	if(bytes==-1)err();
	if(ack != synack+1)err();
	
	return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
	int bytes;
	//3 client making private pipe
	char PP[8];
	srand(time(NULL));
	sprintf(PP, "%s%d", "PP", rand()%10000);
	if(mkfifo(PP, 0666)==-1)err();
	
	//3 client opening wkp (unblocking server)
	*to_server = open(WKP, O_WRONLY, 0);
	if(*to_server==-1)err();

	//3 Client Writing PP to WKP (matches with step 5)
	bytes = write(*to_server, PP, sizeof(PP));
	if(bytes==-1)err();	
	
	//3 Client Opening PP [BLOCKS]
	int from_server = open(PP, O_RDONLY, 0);

	//8 client delete pp
	remove(PP);
	
	//8 Client reading SYN_ACK (matches with step 7)
	int synack;
	bytes = read(from_server, &synack, 4);
	if(bytes==-1)err();
	
	//8 Client Sending (matches with step 9) ACK
	int ack = synack +1;
	bytes = write(*to_server, &ack, 4);
	if(bytes==-1)err();
	
	return from_server;
}

void server_handshake_half(int *to_client, int from_client){
	//printf("setup was fine, omw finish up handshake\n");
	int bytes = 0;
	
	char PP[8];
	bytes = read(from_client, PP, 8);
	if(bytes!=8)err();
	
	//6 Server opening the Private Pipe [Unblock client]	
	*to_client = open(PP, O_WRONLY, 0);
	
	//7 Server sending SYN_ACK	
	srand(time(NULL));
	int synack = rand();
	bytes = write(*to_client, &synack, 4);
	if(bytes==-1)err();
	
	//9 Server reading final ACK
	int ack;
	bytes = read(from_client, &ack, 4);
	if(bytes==-1)err();
	if(ack != synack+1)err();	
	
	//printf("handshake all clear!\n");
}

int err(){
	printf("errno %d\n", errno);
	strerror(errno);
	printf("%s\n", strerror(errno));
	exit(0);
}

/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
*/



