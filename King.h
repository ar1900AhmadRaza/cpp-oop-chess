#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King();
	King(char color, int row, int col);
	bool valid_move(int row, int column, Piece* board[8][8]) override;
};