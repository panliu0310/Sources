/* CSCI1540
 *
 * Assignment: 5
 * Student ID: 1155127464
 * Name: Liu Hoi Pan
 * Email: 1155127464@link.cuhk.edu.hk
 */
#include <iostream>
#include <iomanip>
using namespace std;

const int N = 11;

//function prototype

void PrintBoard(char[][N]);
int CheckValid(char board[][N], char column, int row);
int CheckWinChain(char board[][N], char player, char column, int row);

//function

void PrintBoard(char board[][N])//print the game board
{
	cout << setw(2) << "  A B C D E F G H I J K" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << setw(i + 2) << i << " ";
		for (int j = 0; j < N; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

int CheckValid(char board[][N], char column, int row)//check validity
{
	int columnInt = 11;

	if (column == 'A')columnInt = 0; if (column == 'B')columnInt = 1; if (column == 'C')columnInt = 2; if (column == 'D')columnInt = 3; if (column == 'E')columnInt = 4; if (column == 'F')columnInt = 5; if (column == 'G')columnInt = 6; if (column == 'H')columnInt = 7; if (column == 'I')columnInt = 8; if (column == 'J')columnInt = 9; if (column == 'K')columnInt = 10;
	//convert char to int

	if ((columnInt < 0 || columnInt > 10) || (row < 0 || row > 10))//not a proper cell location
		return 0;
	if (board[row][columnInt] != '.')
		return 0;
	return 1;
}

int CheckWinChain(char board[][N], char player, char column, int row)
{
	bool ReachableArray[N][N];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			ReachableArray[i][j] = 0;
		}
	}
	//create reachable array

	int columnInt = 0;
	if (column == 'A')columnInt = 0; if (column == 'B')columnInt = 1; if (column == 'C')columnInt = 2; if (column == 'D')columnInt = 3; if (column == 'E')columnInt = 4; if (column == 'F')columnInt = 5; if (column == 'G')columnInt = 6; if (column == 'H')columnInt = 7; if (column == 'I')columnInt = 8; if (column == 'J')columnInt = 9; if (column == 'K')columnInt = 10;
	//convert char to int

	ReachableArray[row][columnInt] = 1;

	for (int k = 0; k < 61; k++)
	{
		for (int row2 = 1; row2 < N - 1; row2++)//case: 0 < row < N - 1, 0 < column < N - 1
			for (int columnInt2 = 1; columnInt2 < N - 1; columnInt2++)
				for (int i = -1; i <= 1; i++)
				{
					if (ReachableArray[row2][columnInt2] == 1 && board[row2 + i][columnInt2] == player)ReachableArray[row2 + i][columnInt2] = 1;
					if (ReachableArray[row2][columnInt2] == 1 && board[row2][columnInt2 + i] == player)ReachableArray[row2][columnInt2 + i] = 1;
					if (ReachableArray[row2][columnInt2] == 1 && board[row2 + i][columnInt2 - i] == player)ReachableArray[row2 + i][columnInt2 - i] = 1;
				}
		for (int row3 = 1; row3 < N - 1; row3++)//case: 0 < row < N - 1, column = 0
			for (int i = -1; i <= 1; i++)
			{
				if (ReachableArray[row3][0] == 1 && board[row3 + i][0] == player)ReachableArray[row3 + i][0] = 1;
				if (ReachableArray[row3][0] == 1 && board[row3][1] == player)ReachableArray[row3][1] = 1;
				if (ReachableArray[row3][0] == 1 && board[row3 - 1][1] == player)ReachableArray[row3 - 1][1] = 1;
			}
		for (int row4 = 1; row4 < N - 1; row4++)//case: 0 < row < N - 1, column = N - 1
			for (int i = -1; i <= 1; i++)
			{
				if (ReachableArray[row4][N - 1] == 1 && board[row4 + i][N - 1] == player)ReachableArray[row4 + i][N - 1] = 1;
				if (ReachableArray[row4][N - 1] == 1 && board[row4][N - 2] == player)ReachableArray[row4][N - 2] = 1;
				if (ReachableArray[row4][N - 1] == 1 && board[row4 + 1][N - 2] == player)ReachableArray[row4 + 1][N - 2] = 1;
			}
		for (int columnInt3 = 1; columnInt3 < N - 1; columnInt3++)//case: row = 0, 0 < column < N- 1
			for (int i = -1; i <= 1; i++)
			{
				if (ReachableArray[0][columnInt3] == 1 && board[0][columnInt3 + i] == player)ReachableArray[0][columnInt3 + i] = 1;
				if (ReachableArray[0][columnInt3] == 1 && board[1][columnInt3] == player)ReachableArray[1][columnInt3] = 1;
				if (ReachableArray[0][columnInt3] == 1 && board[1][columnInt3 - 1] == player)ReachableArray[1][columnInt3 - 1] = 1;
			}
		for (int columnInt4 = 1; columnInt4 < N - 1; columnInt4++)//case: row = N - 1, 0 < column < N - 1
			for (int i = -1; i <= 1; i++)
			{
				if (ReachableArray[N - 1][columnInt4] == 1 && board[N - 1][columnInt4 + i] == player)ReachableArray[N - 1][columnInt4 + i] = 1;
				if (ReachableArray[N - 1][columnInt4] == 1 && board[N - 2][columnInt4] == player)ReachableArray[N - 2][columnInt4] = 1;
				if (ReachableArray[N - 1][columnInt4] == 1 && board[N - 2][columnInt4 + 1] == player)ReachableArray[N - 2][columnInt4 + 1] = 1;
			}
		if (ReachableArray[0][0] == 1 && board[1][0] == player)ReachableArray[1][0] = 1;//case: row = 0, column = 0
		if (ReachableArray[0][0] == 1 && board[0][1] == player)ReachableArray[0][1] = 1;
		if (ReachableArray[0][N - 1] == 1 && board[1][N - 1] == player)ReachableArray[1][N - 1] = 1;//case: row = 0, column = N - 1
		if (ReachableArray[0][N - 1] == 1 && board[0][N - 2] == player)ReachableArray[0][N - 2] = 1;
		if (ReachableArray[0][N - 1] == 1 && board[1][N - 2] == player)ReachableArray[1][N - 2] = 1;
		if (ReachableArray[N - 1][0] == 1 && board[N - 2][0] == player)ReachableArray[N - 2][0] = 1;//case: row = N - 1, column = 0
		if (ReachableArray[N - 1][0] == 1 && board[N - 1][1] == player)ReachableArray[N - 1][1] = 1;
		if (ReachableArray[N - 1][0] == 1 && board[N - 2][1] == player)ReachableArray[N - 2][1] = 1;
		if (ReachableArray[N - 1][N - 1] == 1 && board[N - 2][N - 1] == player)ReachableArray[N - 2][N - 1] = 1;//case: row = N - 1, column = N - 1
		if (ReachableArray[N - 1][N - 1] == 1 && board[N - 1][N - 2] == player)ReachableArray[N - 1][N - 2] = 1;
	}
	//Set Reachability to all array in ReachableArray

	for (row = 0; row <= N - 1; row++)
		for (int Row = 0; Row <= N - 1; Row++)
			if (ReachableArray[row][0] == 1 && ReachableArray[Row][10] == 1 && player == 'X')
				return 1;
	//Check win chain for player 'O'
	for (columnInt = 0; columnInt <= N - 1; columnInt++)
		for (int ColumnInt = 0; ColumnInt <= N - 1; ColumnInt++)
			if (ReachableArray[0][columnInt] == 1 && ReachableArray[10][ColumnInt] == 1 && player == 'O')
				return 2;
	//Check win chain for player 'X'
	return 0;
}

//main function

int main()
{
	//initial condition
	char board[N][N];
	char player = 'O';
	char column = '0'; int row = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j] = '.';
		}
	}
	//initial condition

	while (CheckWinChain(board, player, column, row) == 0)
	{
		PrintBoard(board);

		cout << "Player " << player << " moves: ";
		cin >> column >> row;

		while (CheckValid(board, column, row) == 0) //Check the validity
		{
			cout << "Invalid! Try again." << endl;
			cout << "Player " << player << " moves: ";
			cin >> column >> row;
		}

		//update the game board
		int columnInt = 0;
		if (column == 'A')columnInt = 0; if (column == 'B')columnInt = 1; if (column == 'C')columnInt = 2; if (column == 'D')columnInt = 3; if (column == 'E')columnInt = 4; if (column == 'F')columnInt = 5; if (column == 'G')columnInt = 6; if (column == 'H')columnInt = 7; if (column == 'I')columnInt = 8; if (column == 'J')columnInt = 9; if (column == 'K')columnInt = 10;
		//convert char to int
		board[row][columnInt] = player;
		//update the game board

		if (player == 'O')player = 'X';
		else player = 'O';
		//update the player
	}
	if (CheckWinChain(board, player, column, row) == 1)
	{
		PrintBoard(board);
		cout << "Player O Wins!";
	}
	if (CheckWinChain(board, player, column, row) == 2)
	{
		PrintBoard(board);
		cout << "Player X wins!";
	}
	
	return 0;
}