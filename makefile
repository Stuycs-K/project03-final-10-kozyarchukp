run: rps
	@./rps
compile rps: rps.o server.o client.o pipe_networking.o username.o pipe_networking.h
	@gcc -g -o rps rps.o server.o client.o pipe_networking.o username.o
rps.o: rps.c pipe_networking.h
	@gcc -c rps.c
server.o: server.c pipe_networking.h 
	@gcc -c server.c 
client.o: client.c pipe_networking.h 
	@gcc -c -g client.c 
pipe_networking.o: pipe_networking.c pipe_networking.h 
	@gcc -c -g pipe_networking.c 
username.o: username.c pipe_networking.h
	@gcc -c -g username.c
clear:
	rm *.o
	rm rps