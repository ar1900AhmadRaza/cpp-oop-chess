#include "King.h"
King::King() : Piece(){}
King::King(char color, int row, int col) : Piece(color, row, col, 'K'){}
bool King::valid_move(int row, int column, Piece* board[8][8])
{
	int from_row = get_row_num();
	int from_column = get_column_num();
	int distance_row = abs(row - from_row);
	int distnace_column = abs(column - from_column);
	if (distance_row > 1 || distnace_column > 1)
	{
		return false;
	}
	if (board[row][column] != nullptr && board[row][column]->get_colour() == get_colour())
	{
		return false;
	}
	return true;
}
