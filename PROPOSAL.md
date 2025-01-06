# Final Project Proposal

## Group Members:

Polina Kozyarchuk
       
# Intentions:

Rock, Paper Scissors

# Intended usage:

Upon running, type in username and password.  
To check your statisics -- 'stats'  
To check leaderboard -- 'leaderboard'  
To start a game -- 'new game'  
To join a game -- 'join game'  
If you started the game:  
    select number of rounds
    select number of players (including self, from 2-10)  
    wait for the expected number of players to join  
    
If joining game:  
    wait for a new game to be started  
    once ready, automatically be added to the new game  
    wait for the expected number of players to join  
    
The rest is the same for both:  
    Once all players have joined, the first round automatically starts  
    Type either rock, paper or scissors  
    Once all players have inputed, result of round is revealed  
    round is repeated indefintely until there is a clear winner, only then do you go to the next round  
    Once all rounds are finished, game ends.  
    
# Technical Details:

- Allocating memory, when taking in user input
- Working with files, when storing usernames/passwords and their wins
- Finding information about files, when storing usernames/passwords
- Pipes, named. 'new game' will be a server, 'join game' will be a client.
- Processes, will need to make a forking server to handle multiple clients
    
# Intended pacing:

Jan 9: MVP. literally just a server that will start the game and a client that will respond to it.  
Jan 13: usernames  
Jan 15: w/l ratios ('stat')  
Jan 18: supporting 3+ players  
Jan 20: leaderboard  
