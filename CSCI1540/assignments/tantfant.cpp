/* CSCI1540
 *
 * Assignment: 4
 * Student ID: 1155127464
 * Name: Liu Hoi Pan
 * Email: 1155127464@link.cuhk.edu.hk
 */
#include <iostream>
using namespace std;

/* Function prototypes. DO NOT MODIFY! */
int status(int board, int pos);
void printBoard(int board);
void updateBoard(int& board, int from, int to, int p);
int formLine(int board);

/* Returns the status of position pos of the game board. DO NOT MODIFY! */
int status(int board, int pos) {
	for (int i = 0; i < 9 - pos; i++)
		board /= 10;
	return board % 10;
}

/* Prints the board to the screen. DO NOT MODIFY! */
void printBoard(int board) {
	cout << status(board, 1) << "-" << status(board, 2) << "-" << status(board, 3) << endl;
	cout << "|\\|/|\n";
	cout << status(board, 4) << "-" << status(board, 5) << "-" << status(board, 6) << endl;
	cout << "|/|\\|\n";
	cout << status(board, 7) << "-" << status(board, 8) << "-" << status(board, 9) << endl;
}

/* Updates the from-th digit of board to 0, and the to-th digit of board to
   digit p. The other digits of board remain unchanged.  */
void updateBoard(int& board, int from, int to, int p) {
	int from1 = p;
	for (from; 9 - from > 0; from++)
	{
		from1 *= 10;
	}
	int to1 = p;
	for (to; 9 - to > 0; to++)
	{
		to1 *= 10;
	}
	board = board - from1 + to1; //update the value of board
}

/* Checks if any player has formed a line horizontally, vertically, or
   diagonally in board except his/her home row. */
int formLine(int board) {
	if (status(board, 4) == 1 && status(board, 5) == 1 && status(board, 6) == 1)return 1;//player 1, row 2
	if (status(board, 7) == 1 && status(board, 8) == 1 && status(board, 9) == 1)return 1;//player 1, row 3
	if (status(board, 1) == 1 && status(board, 4) == 1 && status(board, 7) == 1)return 1;//player 1, column 1
	if (status(board, 2) == 1 && status(board, 5) == 1 && status(board, 8) == 1)return 1;//player 1, column 2
	if (status(board, 3) == 1 && status(board, 6) == 1 && status(board, 9) == 1)return 1;//player 1, column 3
	if (status(board, 1) == 1 && status(board, 5) == 1 && status(board, 9) == 1)return 1;//player 1, diagonal 1
	if (status(board, 3) == 1 && status(board, 5) == 1 && status(board, 7) == 1)return 1;//player 1, diagonal 2
	if (status(board, 1) == 2 && status(board, 2) == 2 && status(board, 3) == 2)return 2;//player 2, row 1
	if (status(board, 4) == 2 && status(board, 5) == 2 && status(board, 6) == 2)return 2;//player 2, row 2
	if (status(board, 1) == 2 && status(board, 4) == 2 && status(board, 7) == 2)return 2;//player 2, column 1
	if (status(board, 2) == 2 && status(board, 5) == 2 && status(board, 8) == 2)return 2;//player 2, column 2
	if (status(board, 3) == 2 && status(board, 6) == 2 && status(board, 9) == 2)return 2;//player 2, column 3
	if (status(board, 1) == 2 && status(board, 5) == 2 && status(board, 9) == 2)return 2;//player 2, diagonal 1
	if (status(board, 3) == 2 && status(board, 5) == 2 && status(board, 7) == 2)return 2;//player 2, diagonal 2
	return 0;
}

int main() {
	int board = 111000222;
	int p = 1;

	while (formLine(board) == 0)
	{
		printBoard(board);
		int from, to;
		cout << "Player " << p << " (from to): ";
		cin >> from >> to;
		int check = 0;
		while (check < 4)//this while loop can check the from, to values are valid or not. If it is invalid, one cannot escape the loop
		{
			check = 0;
			if ((from > 0 && from < 10) && (to > 0 && to < 10))check++;//two input positions are 1¡V9,
			if (status(board,from) == p)check++;// the source position is occupied by the current player
			if (status(board,to) == 0)check++;// the destination position is empty
			if ((from == 1 && to == 2) || (from == 1 && to == 4) || (from == 1 && to == 5))check++;// the source and destination positions are adjacent(case: from == 1)
			if ((from == 2 && to == 1) || (from == 2 && to == 3) || (from == 2 && to == 5))check++;// the source and destination positions are adjacent(case: from == 2)
			if ((from == 3 && to == 2) || (from == 3 && to == 5) || (from == 3 && to == 6))check++;// the source and destination positions are adjacent(case: from == 3)
			if ((from == 4 && to == 1) || (from == 4 && to == 5) || (from == 4 && to == 7))check++;// the source and destination positions are adjacent(case: from == 4)
			if (from == 5 && to != 5) check++;// the source and destination positions are adjacent(case: from == 5)
			if ((from == 6 && to == 3) || (from == 6 && to == 5) || (from == 6 && to == 9))check++;// the source and destination positions are adjacent(case: from == 6)
			if ((from == 7 && to == 4) || (from == 7 && to == 5) || (from == 7 && to == 8))check++;// the source and destination positions are adjacent(case: from == 7)
			if ((from == 8 && to == 5) || (from == 8 && to == 7) || (from == 8 && to == 9))check++;// the source and destination positions are adjacent(case: from == 8)
			if ((from == 9 && to == 5) || (from == 9 && to == 6) || (from == 9 && to == 8))check++;// the source and destination positions are adjacent(case: from == 9)
			if (check < 4) 
			{
				cout << "Invalid. Try again!" << endl << "Player " << p << " (from to) : ";
				cin >> from >> to;
			}
		}
		updateBoard(board, from, to, p);
		if (p == 1)p++;
		else p--;
	}
	if (formLine(board) == 1) 
	{
		printBoard(board);
		cout << "Player 1 wins!";
	}
	if (formLine(board) == 2) 
	{
		printBoard(board);
		cout << "Player 2 wins!";
	}
	return 0;
}