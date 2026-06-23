#pragma once
#include "Piece.h"
class Pawn : public Piece
{
	bool moved_before;
public:
	Pawn();
	Pawn(char color, int row, int col);
	void set_moved_before();
	bool valid_move(int row, int col, Piece* board[8][8]) override;
};