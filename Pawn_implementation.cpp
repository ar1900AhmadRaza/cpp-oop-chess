#include "Pawn.h"
#include <cmath>
Pawn::Pawn() : Piece()
{
	this->moved_before = false;
}
Pawn::Pawn(char color, int row, int col) : Piece(color, row, col, 'P')
{
	this->moved_before = false;
}
void Pawn::set_moved_before()
{
	this->moved_before = true;
}
bool Pawn::valid_move(int row, int col, Piece* board[8][8])
{
	int from_row = get_row_num();
	int from_column = get_column_num();
	char color = get_colour();

	int direction;
	if (color == 'W')
	{
		direction = -1; // White moves up (decreasing row index)
	}
	else
	{
		direction = 1;  // Black moves down (increasing row index)
	}
	// Move one square forward
	if (from_column == col && row == from_row + direction && board[row][col] == nullptr)
	{
		return true;
	}
	// Move two squares forward
	if (!moved_before && col == from_column && row == from_row + 2 * direction &&  // pawn can only jum 2 squares at its first moves
		board[from_row + direction][from_column] == nullptr && board[row][col] == nullptr)
	{
		return true;
	}
	// Diagonal capture
	if (row == from_row + direction && abs(col - from_column) == 1 &&
		board[row][col] != nullptr && board[row][col]->get_colour() != color)
	{
		return true;
	}
	return false;
}