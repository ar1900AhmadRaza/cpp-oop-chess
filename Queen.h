#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen();
	Queen(char color, int row, int col);
	bool valid_move(int row, int column, Piece* board[8][8]) override;
};