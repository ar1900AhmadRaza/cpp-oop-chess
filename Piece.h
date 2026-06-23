#pragma once
#include <iostream>
using namespace std;
class Piece
{
	char colour;
	int row_num;
	int column_num;
	char symbol;
	bool is_alive;
public:
	Piece();
	Piece(char color, int row, int col, char symbol);
	char get_colour() const;
	int get_row_num() const;
	int get_column_num() const;
	char get_symbol() const;
	bool get_is_alive() const;
	void set_position(int r, int c);
	void capture();
	virtual bool valid_move(int row, int column, Piece* board[8][8]) = 0; // pure virtual function // why piece*? because it is an abstract class we can't create just piece array here and we have to set nullptr if square is empty and only pointer can do that
	virtual ~Piece();
};