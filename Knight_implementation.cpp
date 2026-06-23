#include "Knight.h"
Knight::Knight() : Piece(){}
Knight::Knight(char color, int row, int col) : Piece(color, row, col, 'N'){}
bool Knight::valid_move(int row, int column, Piece* board[8][8])
{
	int from_row = get_row_num();
	int from_column = get_column_num();
	int distance_row = abs(row - from_row);
	int distance_column = abs(column - from_column);
	if (distance_row * distance_column != 2)     // only movement (2,1) or (1,2)
		return false;
	if (board[row][column] != nullptr && board[row][column]->get_colour() == get_colour())
		return false;
	return true;
}
