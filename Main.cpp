// ============================================================================
//                          CHESS GAME — MAIN ENTRY
// ============================================================================
// A fully object-oriented console chess game in C++.
//
// OOP Concepts Demonstrated:
//   • Inheritance    — All piece types derive from abstract Piece base class
//   • Polymorphism   — Board calls valid_move() uniformly via Piece* pointers
//   • Encapsulation  — Board hides grid internals; controlled public interface
//   • Composition    — Game has-a Board, Board has-a collection of Pieces
//   • Exception Hierarchy — Custom exceptions inheriting from std::exception
//
// To compile:
//   g++ -std=c++11 main.cpp *_implementation.cpp -o chess
//   ./chess
// ============================================================================

#include "Game.h"

int main() {
    Game chessGame;
    chessGame.run();
    return 0;
}
