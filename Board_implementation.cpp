#include "Board.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>

using namespace std;

Board::Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            Grid[i][j] = nullptr;

    Grid[0][0] = new Rook  ('B', 0, 0); Grid[0][1] = new Knight('B', 0, 1);
    Grid[0][2] = new Bishop('B', 0, 2); Grid[0][3] = new Queen ('B', 0, 3);
    Grid[0][4] = new King  ('B', 0, 4); Grid[0][5] = new Bishop('B', 0, 5);
    Grid[0][6] = new Knight('B', 0, 6); Grid[0][7] = new Rook  ('B', 0, 7);

    for (int j = 0; j < 8; j++) Grid[1][j] = new Pawn('B', 1, j);
    for (int j = 0; j < 8; j++) Grid[6][j] = new Pawn('W', 6, j);

    Grid[7][0] = new Rook  ('W', 7, 0); Grid[7][1] = new Knight('W', 7, 1);
    Grid[7][2] = new Bishop('W', 7, 2); Grid[7][3] = new Queen ('W', 7, 3);
    Grid[7][4] = new King  ('W', 7, 4); Grid[7][5] = new Bishop('W', 7, 5);
    Grid[7][6] = new Knight('W', 7, 6); Grid[7][7] = new Rook  ('W', 7, 7);
}

Board::~Board()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        { delete Grid[i][j]; Grid[i][j] = nullptr; }
}

Piece* Board::get_piece(int row, int col) const { return Grid[row][col]; }

// ─── display: Board with dynamic turn-based border/label colors ────────────────
void Board::display(char current_turn) const
{
    system("cls || clear");

    const string RESET             = "\033[0m";
    const string COLOR_WHITE_PIECE = "\033[96m";  // Bright Cyan
    const string COLOR_BLACK_PIECE = "\033[91m";  // Bright Red
    const string COLOR_DARK_SQ    = "\033[90m";   // Dark Grey for "::"

    // Cyan border when White's turn, Red when Black's turn
    const string B = (current_turn == 'W') ? "\033[96m" : "\033[91m";
    const string L = B;  // labels same as border

    cout << "\n";
    cout << L  << "      A    B    C    D    E    F    G    H" << RESET << "\n";
    cout << B  << "    +----+----+----+----+----+----+----+----+" << RESET << "\n";

    for (int i = 0; i < 8; i++)
    {
        cout << L << "  " << (8 - i) << " |" << RESET;

        for (int j = 0; j < 8; j++)
        {
            if (Grid[i][j] != nullptr)
            {
                char clr = Grid[i][j]->get_colour();
                char sym = Grid[i][j]->get_symbol();
                const string& PC = (clr == 'W') ? COLOR_WHITE_PIECE : COLOR_BLACK_PIECE;
                cout << " " << PC << clr << sym << RESET << " ";
            }
            else
            {
                if ((i + j) % 2 == 0)
                    cout << " " << COLOR_DARK_SQ << "::" << RESET << " ";
                else
                    cout << "    ";
            }
            cout << B << "|" << RESET;
        }
        cout << L << " " << (8 - i) << RESET << "\n";
        cout << B << "    +----+----+----+----+----+----+----+----+" << RESET << "\n";
    }

    cout << L << "      A    B    C    D    E    F    G    H" << RESET << "\n\n";
}

bool Board::is_in_check(char color) const
{
    int king_row = -1, king_col = -1;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (Grid[i][j] && Grid[i][j]->get_colour() == color && Grid[i][j]->get_symbol() == 'K')
            { king_row = i; king_col = j; }

    if (king_row == -1) return false;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (Grid[i][j] && Grid[i][j]->get_colour() != color)
                if (Grid[i][j]->valid_move(king_row, king_col, (Piece*(*)[8])Grid))
                    return true;
    return false;
}

bool Board::make_move(int fr, int fc, int tr, int tc, char current_turn)
{
    if (fr<0||fr>7||fc<0||fc>7||tr<0||tr>7||tc<0||tc>7) return false;
    if (!Grid[fr][fc]) return false;
    if (Grid[fr][fc]->get_colour() != current_turn) return false;
    if (!Grid[fr][fc]->valid_move(tr, tc, (Piece*(*)[8])Grid)) return false;

    Piece* moving   = Grid[fr][fc];
    Piece* captured = Grid[tr][tc];
    Grid[tr][tc] = moving; Grid[fr][fc] = nullptr;
    moving->set_position(tr, tc);

    if (is_in_check(current_turn))
    {
        Grid[fr][fc] = moving; Grid[tr][tc] = captured;
        moving->set_position(fr, fc);
        return false;
    }

    if (captured) { captured->capture(); delete captured; }
    if (moving->get_symbol() == 'P')
        static_cast<Pawn*>(moving)->set_moved_before();
    return true;
}

bool Board::has_no_legal_moves(char color)
{
    for (int fr = 0; fr < 8; fr++)
    for (int fc = 0; fc < 8; fc++)
    {
        if (!Grid[fr][fc] || Grid[fr][fc]->get_colour() != color) continue;
        for (int tr = 0; tr < 8; tr++)
        for (int tc = 0; tc < 8; tc++)
        {
            if (!Grid[fr][fc]->valid_move(tr, tc, (Piece*(*)[8])Grid)) continue;
            Piece* m = Grid[fr][fc]; Piece* cap = Grid[tr][tc];
            Grid[tr][tc] = m; Grid[fr][fc] = nullptr; m->set_position(tr, tc);
            bool inchk = is_in_check(color);
            Grid[fr][fc] = m; Grid[tr][tc] = cap; m->set_position(fr, fc);
            if (!inchk) return false;
        }
    }
    return true;
}
