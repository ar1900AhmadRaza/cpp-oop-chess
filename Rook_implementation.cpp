#include "Rook.h"
Rook::Rook() : Piece(){}
Rook::Rook(char color, int row, int col) : Piece(color, row, col, 'R'){}
bool Rook::valid_move(int row, int column, Piece* board[8][8])
{
	int from_row = get_row_num();
	int from_column = get_column_num();
	if (from_row != row && from_column != column)  // no movement diagnally
	{
		return false;
	}
	// Horizontal
	if (from_row == row)
	{
		if (column > from_column) // move right
		{
			for (int i = from_column + 1; i < column; i++)
			{
				if (board[from_row][i] != nullptr)
				{
					return false;       // horizontal path is not clear
				}
			}
		}
		else       // move left
		{
			for (int i = from_column - 1; i > column; i--)
			{
				if (board[from_row][i] != nullptr)
				{
					return false;        // horizontal path not clear
				}
			}
		}
	}
	// Vertical
	if (from_column == column)
	{
		if (row > from_row)   // move down
		{
			for (int i = from_row + 1; i < row; i++)
			{
				if (board[i][from_column] != nullptr)
				{
					return false;      // vertical path not clear
				}
			}
		}
		else       // move up
		{
			for (int i = from_row - 1; i > row; i--)
			{
				if (board[i][from_column] != nullptr)
				{
					return false;      // vertical path not clear
				}
			}
		}
	}
	if (board[row][column] != nullptr && board[row][column]->get_colour() == get_colour())
	{
		return false;
	}
	return true;
}


