#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook();
	Rook(char color, int row, int col);
	bool valid_move(int row, int column, Piece* board[8][8]) override;
};