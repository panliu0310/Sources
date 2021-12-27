#include <iostream>
using namespace std;

bool attackingQueens(const char board[][8]);

bool attackingQueens(const char board[][8])
{
	int count = 0;// check if there are two pieces left on the chessboard board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != '.')count++;
		}
	}
	if (count != 2) return false;// check if there are two pieces left on the chessboard board

	int QExist = 0, qExist = 0;// the two pieces left on board are exactly two opposition queens
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == 'Q')QExist++;
			if (board[i][j] == 'q')qExist++;
		}
	}
	if (QExist != 1 && qExist != 1) return false;// the two pieces left on board are exactly two opposition queens

	for (int i = 0; i < 8; i++)// the two opposition queens attack each other on the chessboard (case 1)
	{
		int rowCount = 0;
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != '.')rowCount++;
		}
		if (rowCount == 2) return true;
	}// in the case that two queens are on the same row

	for (int j = 0; j < 8; j++)// the two opposition queens attack each other on the chessboard (case 2)
	{
		int columnCount = 0;
		for (int i = 0; i < 8; i++)
		{
			if (board[i][j] != '.')columnCount++;
		}
		if (columnCount == 2) return true;
	}// in the case that two queens are on the same column

	for (int i = 6; i > 0; i--)// the two opposition queens attack each other on the chessboard (case 3)
	{
		int diagonalCount = 0;
		for (int j = 0; j < 8; j++)
		{
			if (board[i + j][j] != '.') diagonalCount++;
			if (i + j == 7) continue;// ensure array will not be out of bound
		}
		if (diagonalCount == 2) return true;
	}// in the case that two queens are on the same diagonal, left top corner to right bottom corner, start from board[6][0] to board[1][0]

	int diagonalCount = 0;// the two opposition queens attack each other on the chessboard (case 4)
	for (int i = 0; i < 8; i++)
	{
		if (board[i][i] != '.') diagonalCount++;
	}
	if (diagonalCount == 2) return true;// in the case that two queens are on the same diagonal, left top corner to right bottom corner, start from board[0][0]

	for (int i = 0; i < 7; i++)// the two opposition queens attack each other on the chessboard (case 5)
	{
		for (int j = 1; j < 7; j++)
		{
			int diagonalCount = 0;
			if (board[j][i + j] != '.') diagonalCount++;
			if (i + j == 7) continue;// ensure array will not be out of bound
		}
		if (diagonalCount == 2) return true;
	}// in the case that two queens are on the same diagonal, left bottom corner to right top corner, start from board[0][1] to board[0][6]

	for (int i = 1; i < 7; i++)// the two opposition queens attack each other on the chessboard (case 6)
	{
		int diagonalCount = 0;
		for (int j = 0; j < 7; j++)
		{
			if (board[i - j][j] != '.') diagonalCount++;
			if (i - j == 0) continue;// ensure array will not be out of bound
		}
		if (diagonalCount == 2) return true;
	}// in the case that two queens are on the same diagonal, left bottom corner to right top corner, start from board[1][0] to board[6][0]

	int diagonalCount2 = 0;// the two opposition queens attack each other on the chessboard (case 7)
	for (int i = 0; i < 8; i++)
	{
		if (board[7 - i][i] != '.') diagonalCount2++;
	}
	if (diagonalCount2 == 2) return true;// in the case that two queens are on the same diagonal, left bottom corner to right top corner, start from board[7][0]

	for (int i = 7; i > 1; i--)// the two opposition queens attack each other on the chessboard (case 8)
	{
		int diagonalCount = 0;
		for (int j = 0; j < 7; j++)
		{
			if (board[i - j][j + 1] != '.') diagonalCount++;
		}
		if (diagonalCount == 2) return true;
	}// in the case that two queens are on the same diagonal, left bottom corner to right top corner, start from board[7][1] to board[7][6]
}

int main()
{	
	char board[8][8];
	for (int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			board[i][j] = '.';
		}
	}
	board[1][3] = 'Q'; board[4][6] = 'q';
	cout << attackingQueens(board);
	return 0;
}