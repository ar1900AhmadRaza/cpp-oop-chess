#include "Bishop.h"
Bishop::Bishop() : Piece(){}
Bishop::Bishop(char color, int row, int col) : Piece(color, row, col, 'B'){}
bool Bishop::valid_move(int row, int column, Piece* board[8][8])
{
	int from_row = get_row_num();
	int from_column = get_column_num();
	int distance_row = abs(row - from_row);
	int distance_column = abs(column - from_column);
	if (distance_row != distance_column)     // must same like (2,2)(3,3) etc.
		return false;
	// down - right
	if (row > from_row && column > from_column)
	{
		for (int i = from_row + 1, j = from_column + 1; i < row && j < column; i++, j++)
		{
			if (board[i][j] != nullptr)
			{
				return false;
			}
		}
	}
	// up - left
	else if (row < from_row && column < from_column)
	{
		for (int i = from_row - 1, j = from_column - 1; i > row && j > column; i--, j--)
		{
			if (board[i][j] != nullptr)
			{
				return false;
			}
		}
	}
	// up - right
	else if (row < from_row&& column > from_column)
	{
		for (int i = from_row - 1, j = from_column + 1; i > row && j < column; i--, j++)
		{
			if (board[i][j] != nullptr)
			{
				return false;
			}
		}
	}
	// down - left
	else if (row > from_row&& column < from_column)
	{
		for (int i = from_row + 1, j = from_column - 1; i < row && j > column; i++, j--)
		{
			if (board[i][j] != nullptr)
			{
				return false;
			}
		}
	}
	if (board[row][column] != nullptr && board[row][column]->get_colour() == get_colour())
		return false;
	return true;
}