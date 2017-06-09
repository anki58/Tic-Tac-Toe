///TIC TAC TOE ASSIGNMENT PART 2////////////////////////////////////////////
////Assignment 2-group 1//////////////////////////////////////////////
///group members:Anuradha Ramprasad,Ankita Sawant,Sahar Eshraghi//////
///Date of submission: 02/10/2016/////////////////////////////////////
/////Note::We have also worked on extra credit

#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

void displayFunction(vector<vector<char>>, int);//To display Game Board
int winnerCheckVerticalFunction(vector<vector<char>>, int, int, char, int, int);//Checking vertical columns for winner
int winnerCheckDigonalFunction(vector<vector<char>>, int, int, char, int, int);//Checking diagonals for winner
int winnerCheckHorizontalFunction(vector<vector<char>>, int, int, char, int, int);//Checking horizontal rows for winner
int winnerCheckSquareFunction(vector<vector<char>>, int, int, char, int, int);
int main();
//Checking horizontal rows for winner
int winnerFunction(vector<vector<char>>, int, int, char, int, int);//checking winner

int main()
{

	int noOfPlayers, boardSize, winCount;
	int flag = 0; int passes = 0, playerCount = 0, move = 0;
	int turns = 0;
	int passings = 0;
	int row, column;
	char whole[10] = "abcdedfgh";
	char passingInSymbol, prevGameFlag, continueFlag;
	vector<char>players{ 'X','O','A','B','C','D','E','F','G','H','I','J','K','L','M','N','P','Q','R','S','T','U','V','W','Y','Z' };

	vector<vector<char>>board(100, vector<char>(100));

	cout << "welcome to play TIC-TAC-TOE:" << endl;

	cout << "Do you want to continue previous game ? (Y=Yes/N=No)" << endl;
	cin >> prevGameFlag;
	if (prevGameFlag == 'Y' || prevGameFlag == 'y')
	{
		//Retriving the previous game-------------------------------------------

		//	cout << "You last game status" << endl;
		ifstream infile("./save_game.txt"); // for input file
		if (infile.fail()) { cout << "Input file  opening failed" << endl; return 1; }

		//#1 ------------size of board------------
		infile >> boardSize;
		board.resize(boardSize, vector<char>(boardSize));
		//	vector<vector<char>>board(boardSize, vector<char>(boardSize));
		int boardSizee = board.size();
		//#2--------------moves-----------------
		for (int i = 0; i < boardSizee; i++)
			for (int j = 0; j < boardSizee; j++)
				infile >> board[i][j];//assign prev vector moves 
									  //#3------------moves count-------------
		infile >> playerCount;
		//#4------------player count -----------      
		infile >> noOfPlayers;
		infile >> passings;
		//cout << "noOfPlayers" << noOfPlayers << endl;
		//#5-------------turns------------------
		infile >> turns;
		//infile >> passings;
		//#6------------win seq------------------
		infile >> winCount;
		infile >> passes;
		//#7-------------flag-------------------

		infile >> flag;

		//cout << "flag:" << flag << endl;

		displayFunction(board, boardSize);
		move = playerCount;
		//passes = noOfPlayers;
		//noOfPlayers = playerCount;


	}


	else {
		cout << "Enter the no.of players taking part in the game: " << endl;
		cin >> noOfPlayers;

		if (noOfPlayers > 26 || noOfPlayers < 2) {
			cout << "the game has a predefined rule to take a minimum of 2 and a maximum of 26 players!" << endl;
			cout << "Please re-enter the No.of players: " << endl;
			cin >> noOfPlayers;
		}

		players.resize(noOfPlayers);


		cout << "Enter the size Board :" << endl;
		cin >> boardSize;

		if (boardSize < noOfPlayers) {
			cout << "The game well playable only if the board size is greater than no.of players!!!" << endl;
			cout << "hence enter another value for board size:\n";
			cin >> boardSize;

		}

		//vector<char>board(boardSize);

		cout << "Enter the win sequence count:" << endl;
		cin >> winCount;

		if (winCount < 3) {
			cout << "The game well playable only if the win count is more than 3!!!" << endl;
			cout << "Hence re-enter a better win count" << endl;
			cin >> winCount;
		}

		board.resize(boardSize, vector<char>(boardSize));

	}

	//vector<vector<char>>board(boardSize, vector<char>(boardSize));


	cout << "Please note : " << endl;
	for (int p = 0; p < noOfPlayers; p++) {

		cout << players[p] << " is the symbol of player -" << p + 1 << endl;
	}
	cout << endl;
	//int b = board.size()*board.size();
	int b = board.size();
	//cout << "boardsize= "<< b<<endl;
	//cout << "flag= " << flag << endl;
	
	while (turns < b) {
		int flagPass = 0;
		//cout << "turns= " << turns << " noOfPlayers:"<<noOfPlayers<<" b"<<b<< endl;
		for (int passes = 0; passes < noOfPlayers; passes++) {
			passings++;
			if (flag == 0) {
				row = 0; column = 0;
				//cout << "move%noOfPlayers" << move%noOfPlayers<<endl;
				//cout << "passes= " << passes << endl;
				if ((prevGameFlag == 'Y' || prevGameFlag == 'y') && flagPass==0)
				{
					cout << "Player - " << players[move%noOfPlayers] << " turn to enter row and column :" << endl;
					passingInSymbol = players[move%noOfPlayers];
				}
				else
				{
					cout << "Player - " << players[passes] << " turn to enter row and column :" << endl;
					passingInSymbol = players[passes];
				}
				//cin >> row >> column;

				while (!(cin >> row)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input. Please give correct row and column: ";
					//passes = passes - 1;
				}

				while (!(cin >> column)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input.  Please give correct row and column: ";
					//passes = passes - 1;
				}
				if ((row > boardSize || column > boardSize) || (row < 1 || column < 1)) {
					cout << "No such column or row exists! " << endl;
					passes = passes - 1;

				}
				else {
					row = row - 1;
					column = column - 1;
					if (board[row][column] != NULL)//logic to avoid the use of same move again
					{
						cout << "Already Occupied! choose a different location! " << endl;
						passes = passes - 1;
						flagPass = 1;
					}
					else {
						board[row][column] = passingInSymbol;

						displayFunction(board, boardSize);
						flag = winnerFunction(board, boardSize, winCount, passingInSymbol, row, column);
						
						if (flag != 1) {
							cout << "Do you want to save the game and continue later?(Y=YES/No)" << endl;
							cin >> continueFlag;
							if (continueFlag == 'Y' || continueFlag == 'y') {

								//Saving Game in File-------------------------------------------
								ofstream output_file("./save_game.txt");
								//#1------------save board dimension to file
								output_file << boardSize << endl;
								int counter = 0;
								for (int i = 0; i < board.size(); i++)
									for (int j = 0; j < board.size(); j++)
									{
										//#2-------------save each move
										output_file << board[i][j] << endl;
										//if (board[i][j] == 'X' || board[i][j] == 'O')
										for (int temp = 0; temp < players.size(); temp++)
										{
											if (board[i][j] == players[temp])
												counter++;
										}

									}
								//#3  --------save number of moves
								output_file << counter << endl;
								//#4-----------save prev players count
								output_file << noOfPlayers << endl;
								output_file << passings<<endl;
								//#5-----------save turns
								output_file << turns + 1 << endl;
								//output_file << passings;

								//#6--------------win seq
								output_file << winCount << endl;
								//	cout << "counter::" << counter << endl;
								//flag = 1;
								//#7--------------flag
								//cout << "flag::" << flag << endl;
								output_file << passes << endl;
								output_file << flag << endl;
								return 0;
							}
						}
					}
				}
				if (passings == (board.size()*board.size())) {
					//cout << "passing checkout " << endl;
					if (flag == 0) {
						cout << "The game is DRAW \n";
					}
					return flag = 0;

				}

			}

			move++;


		}
		//cout << "turns= " << turns << endl;
		//turns++;
	}


	displayFunction(board, boardSize);
	return 0;
}

//check winning condition
int winnerFunction(vector<vector<char>>board, int boardSize, int winCount, char s, int row, int column) {
	int flag = 0;
	if (winnerCheckHorizontalFunction(board, boardSize, winCount, s, row, column) == 1) {
		flag = 1;
		exit(1);
	}
	else if (winnerCheckDigonalFunction(board, boardSize, winCount, s, row, column) == 1)
	{
		flag = 1;
		exit(1);
	}
	else if (winnerCheckVerticalFunction(board, boardSize, winCount, s, row, column) == 1)
	{
		flag = 1;
		exit(1);
	}
	else if (winnerCheckSquareFunction(board, boardSize, winCount, s, row, column) == 1)
	{
		flag = 1;
		exit(1);
	}
	//cout << "within within flag function" <<flag <<endl;
	return flag;
	//return 0;

}
//check horizontal condition
int winnerCheckHorizontalFunction(vector<vector<char>>a, int boardSize, int winCount, char s, int row, int col) {//checking Win condition for rows
	int flag = 0;
	int count = 1;

	for (int i = col - 1; i >= 0; i--)
	{
		if (a[row][i] == s)
			++count;
		else i = -1; // To terminate loop

		if (count >= winCount)
		{
			cout << "\n\nWinner is Player - " << s << endl;//  (Win condition: Row)
			return 1;
		}
	}

	for (int i = col + 1; i < boardSize; i++)
	{
		if (a[row][i] == s)
			++count;
		else i = boardSize; // To terminate loop

		if (count >= winCount)
		{
			cout << "\n\nWinner is Player - " << s<<endl;// (Win condition: Row)
			return 1;
		}
	}

	if (flag == 1) {
		return 1;
	}
	else {
		return 0;
	}

	return flag;

}
//check diagonal condition
int winnerCheckDigonalFunction(vector<vector<char>>a, int boardSize, int winCount, char s, int row, int col)//checking Win condition for diagonal check
{

	int flag = 0;
	int count = 1;

	for (int i = row - 1, j = col - 1;
	i >= 0 && j >= 0;
		i--, j--)
	{
		if (a[i][j] == s)
			++count;
		else i = -1; // To terminate loop 

		if (count >= winCount)
		{
			cout << "\n\nWinner is Player - " << s << endl;// (Win condition: forward diag);
			return 1;
		}
	}

	for (int i = row + 1, j = col + 1;
	i < boardSize && j < boardSize;
		i++, j++)
	{
		if (a[i][j] == s)
			++count;
		else i = boardSize; // To terminate loop

		if (count >= winCount)
		{
			cout << "\n\nWinner is Player - " << s << endl;// << (Win condition: forward diag);
			return 1;
		}
	}

	//Check reverse diagonal - move to top right first then to bottom left

	count = 1;

	for (int i = row - 1, j = col + 1;
	i >= 0 && j < boardSize;
		i--, j++)
	{
		if (a[i][j] == s)
			++count;
		else
		{
			j = boardSize;
		}// To terminate loop

		if (count >= winCount)
		{
			cout << "\n\nWinner is Player - " << s<<endl;// (Win condition : rev diag)
			return 1;
		}

	}

	for (int i = row + 1, j = col - 1;
	i < boardSize && j >= 0;
		i++, j--)
	{
		if (a[i][j] == s)
			++count;
		else i = boardSize; // To terminate loop

		if (count >= winCount)
		{
			cout << "\n\nWinner is Player - " << s << endl;// (Win condition: rev diag)
			return 1;
		}
	}



	if (flag == 1) {
		return 1;
	}
	else {
		return 0;
	}

}
//check vertical condition
int winnerCheckVerticalFunction(vector<vector<char>>a, int boardSize, int winCount, char s, int row, int col)//checking Win condition for columns
{
	int flag = 0;
	//int count = 1;
	char similarVal = NULL;

	int seqCount = 1;

	for (int i = row - 1; i >= 0; i--)
	{
		if (a[i][col] == s)
			++seqCount;
		else i = -1; // To terminate loop

		if (seqCount >= winCount)
		{
			cout << "\n\nWinner is Player - " << s << endl;//  (Win condition: Col)
			return 1;
		}

	}

	for (int i = row + 1; i < boardSize; i++)
	{
		if (a[i][col] == s)
			++seqCount;
		else i = boardSize; // To terminate loop

		if (seqCount >= winCount)
		{
			cout << "\n\nWinner is Player - " << s << endl;//  (Win condition: Col)
			return 1;
		}

	}





	if (flag == 1) {
		return 1;
	}
	else {
		return 0;
	}

}
//check Square condition
int winnerCheckSquareFunction(vector<vector<char>>a, int boardSize, int winCount, char s, int row, int col) {
	int flag = 0;
	//int count = 1;

	//Check square

	
	if (col > 0)//if col > 0, then block 1,2 & 5 is valid. Else out of bounds
	{
		if (a[row][col - 1] == s)
		{
			
			if (row > 0) 
			{
				if (a[row - 1][col - 1] == s && a[row - 1][col] == s)
				{
					cout << "\n\nWinner is Player - " << s<<" satisfying square win function" << endl;// (Win condition: top left square)
					return 1;
				}
			}

			//Loc  5 & 6
			if (row < boardSize - 1) 
			{
				if (a[row + 1][col - 1] == s && a[row + 1][col] == s)
				{
					cout << "\n\nWinner is Player - " << s << " satisfying square win function" << endl;// (Win condition: bot left square)
					return 1;
				}
			}
		}
	}

	

	//Loc 8
	if (col < boardSize - 1) 
	{
		if (a[row][col + 1] == s)
		{
			//Loc  3 & 4
			if (row > 0) //exact same condition as above
			{
				if (a[row - 1][col] == s && a[row - 1][col + 1] == s)
				{
					cout << "\n\nWinner is Player - " << s;// Win condition: top right square
					return 1;
				}
			}

			//Loc  6 & 7
			if (row < boardSize - 1)
			{
				if (a[row + 1][col] == s && a[row + 1][col + 1] == s)
				{
					cout << "\n\nWinner is Player - " << s;// << Win condition: bot right square;
					return 1;
				}
			}
		}
	}


	return flag;



}
//display the game board
void displayFunction(vector<vector<char>>board, int size)
{
	system("CLS");
	//cout << "  1   2   3  \n\n";
	for (int columns = 0; columns < size; columns++) {
		cout << "  " << columns + 1 << " ";
	}
	cout << "  \n\n";
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << " ";
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j];
			if (j < size - 1)
			{
				cout << " | ";
			}
		}
		cout << "\n";

		if (i < size - 1)
		{
			//cout << " ---+---+--- \n";
			cout << " ";
			for (int line = 0; line < size; line++) {
				cout << "---";
				if (line<size - 1) {
					cout << "+";
				}
			}
			cout << " \n";
		}

	}

}