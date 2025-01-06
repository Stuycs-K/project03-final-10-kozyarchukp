#include "rps.h"

/*
	run rps
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

		
}