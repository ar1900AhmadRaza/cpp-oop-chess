#pragma once
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

class Board
{
    Piece* Grid[8][8];
public:
    Board();
    ~Board();

    Piece* get_piece(int row, int col) const;

    // display now takes current_turn to color borders dynamically
    void display(char current_turn) const;

    bool make_move(int from_row, int from_col, int to_row, int to_col, char current_turn);
    bool is_in_check(char color) const;
    bool has_no_legal_moves(char color);
};
