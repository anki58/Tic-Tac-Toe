# Tic-Tac-Toe
Extension of basic tic-tac-toe game for the console. 
Game Instructions:
The game should now work as follows:  
Ask if the player would like to resume a saved game.
If yes, load game state from a text or binary file (your choice of file format).
1. For a new game, ask how many players are playing.
2. For a new game, ask how large the board should be. 
3. For a new game, ask what the win sequence count should be (i.e. 3 in a row). 
4. For a new game, check to ensure that winning is possible given the criteria specified, and display an error if not.  
5. Output a board in the following general format: 

However, you will need to display the correct number of rows/columns based on user input.
6. Ask the user for a row and column number, or if they would like to save and exit. 
If they choose save/exit, do so, otherwise continue.
7. Put the appropriate symbol for that player (X or O) in the specified spot.
Players should be given the following symbols, in order: XOABCDEFGHIJKLMNPQRSTUVWYZ  
8. Repeat for the next player until someone has won the game.
9. If someone has won, announce which player won and exit. If the game has tied, announce that and exit.
The conditions for winning this new tic-tac-toe game are now as follows:   * n in a row/column/diagnoal, where n is the win sequence count   
Extra :  
1. Allow winning by a square whose side dimensions are n - 1, where n is the win sequence count.
For example, the following would be a win for X in a 3x3, n = 3 game:      
1   2   3 1  O | O |   ---+---+--- 2  O | X | X   ---+---+--- 3    | X | X
You may decide for yourself whether squares may be hollow or must be filled in, as long as you clearly tell the user the rules. 
2. Create a "replay" save. As the game is played, save each move to a file. 
When loading the saved game, actually place each player's symbol one at a time with an appropriate delay. 
