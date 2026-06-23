#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop();
	Bishop(char color, int row, int col);
	bool valid_move(int row, int column, Piece* board[8][8]) override;
};