#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight();
	Knight(char color, int row, int col);
	bool valid_move(int row, int column, Piece* board[8][8]) override;
};
