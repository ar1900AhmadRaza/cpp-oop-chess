#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include "Board.h"
#include "Player.h"

using namespace std;

// ─── Custom Exception Hierarchy ───────────────────────────────────────────────
class MoveException : public exception {
protected:
    string errmsg;
public:
    MoveException(string msg) : errmsg(msg) {}
    virtual const char* what() const noexcept { return errmsg.c_str(); }
};

class InvalidSquareFormatException : public MoveException {
public:
    InvalidSquareFormatException(string sq)
        : MoveException("[ERROR] Invalid square format '" + sq + "' — use format like 'e2'") {}
};

class InvalidFileException : public MoveException {
public:
    InvalidFileException(char f)
        : MoveException("[ERROR] File '" + string(1,f) + "' invalid — must be a-h") {}
};

class InvalidRankException : public MoveException {
public:
    InvalidRankException(char r)
        : MoveException("[ERROR] Rank '" + string(1,r) + "' invalid — must be 1-8") {}
};

class EmptyMoveException : public MoveException {
public:
    EmptyMoveException() : MoveException("[ERROR] Move input cannot be empty") {}
};

class IllegalMoveException : public MoveException {
public:
    IllegalMoveException(string from, string to)
        : MoveException("[ERROR] Move " + from + " -> " + to + " is illegal") {}
};

class QuitGameException : public exception {
public:
    virtual const char* what() const noexcept { return "Game ended by player"; }
};

// ─── Game Controller ──────────────────────────────────────────────────────────
class Game {
private:
    Player player1;
    Player player2;
    Board  board;
    char   current_turn;
    bool   game_over;

    bool parse_square(const string& s, int& row, int& col) const;
    bool parse_move_line(const string& line, string& from_str, string& to_str) const;
    void clear_screen()    const;
    void show_welcome()    const;
    void show_turn_header() const;
    void show_game_over(char winner) const;

public:
    Game();
    void run();
    ~Game();
};
