#include "Piece.h"
Piece::Piece()
{
	this->colour = 'N';
	this->row_num = 0;
	this->column_num = 0;
	this->symbol = 'N';
	this->is_alive = true;
}
Piece::Piece(char color, int row, int col, char symbol)
{
	this->colour = color;
	this->row_num = row;
	this->column_num = col;
	this->symbol = symbol;
	this->is_alive = true;
}
char Piece::get_colour() const
{
	return this->colour;
}
int Piece::get_row_num() const
{
	return this->row_num;
}
int Piece::get_column_num() const
{
	return this->column_num;
}
char Piece::get_symbol() const
{
	return this->symbol;
}
bool Piece::get_is_alive() const
{
	return this->is_alive;
}
void Piece::set_position(int r, int c)
{
	this->row_num = r;
	this->column_num = c;
}
void Piece::capture()
{
	this->is_alive = false;
}
Piece::~Piece()
{

}