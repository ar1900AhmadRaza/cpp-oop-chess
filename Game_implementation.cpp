#include "Game.h"
#include <iostream>
#include <cctype>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

// ── ANSI helpers ──────────────────────────────────────────────────────────────
static const string RESET   = "\033[0m";
static const string CYAN    = "\033[96m";
static const string RED     = "\033[91m";
static const string YELLOW  = "\033[93m";
static const string GREEN   = "\033[92m";
static const string BOLD    = "\033[1m";
static const string WHITE_B = "\033[97m";

// Return the active border color based on whose turn it is
static string turn_color(char t) { return (t == 'W') ? CYAN : RED; }

// ─── Cross-Platform Screen Clear ──────────────────────────────────────────────
void Game::clear_screen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ─── Welcome Screen ───────────────────────────────────────────────────────────
void Game::show_welcome() const {
    clear_screen();
    cout << "\n";
    cout << CYAN << "  +=============================================================+" << RESET << "\n";
    cout << CYAN << "  |" << RESET << BOLD << "                                                             " << RESET << CYAN << "|" << RESET << "\n";
    cout << CYAN << "  |" << RESET << BOLD << WHITE_B << "            C H E S S   —   C + +   E D I T I O N           " << RESET << CYAN << "|" << RESET << "\n";
    cout << CYAN << "  |" << RESET << "                                                             " << CYAN << "|" << RESET << "\n";
    cout << CYAN << "  |" << RESET << "              A Classic Game — Built with OOP                " << CYAN << "|" << RESET << "\n";
    cout << CYAN << "  |" << RESET << "                                                             " << CYAN << "|" << RESET << "\n";
    cout << CYAN << "  +=============================================================+" << RESET << "\n";
    cout << "\n";
    cout << YELLOW << "  +-------------------------------------------------------------+" << RESET << "\n";
    cout << YELLOW << "  |" << RESET << "  HOW TO PLAY                                                " << YELLOW << "|" << RESET << "\n";
    cout << YELLOW << "  |" << RESET << "  ------------                                               " << YELLOW << "|" << RESET << "\n";
    cout << YELLOW << "  |" << RESET << "  " << GREEN << "•" << RESET << " Type your move on ONE line:  " << BOLD << "e2 e4" << RESET << "  or  " << BOLD << "e2-e4" << RESET << "          " << YELLOW << "|" << RESET << "\n";
    cout << YELLOW << "  |" << RESET << "  " << GREEN << "•" << RESET << " Columns: a - h   |   Rows: 1 - 8                         " << YELLOW << "|" << RESET << "\n";
    cout << YELLOW << "  |" << RESET << "  " << GREEN << "•" << RESET << " " << CYAN << "Cyan border" << RESET << " = White's turn  |  " << RED << "Red border" << RESET << " = Black's turn    " << YELLOW << "|" << RESET << "\n";
    cout << YELLOW << "  |" << RESET << "  " << GREEN << "•" << RESET << " Type " << BOLD << "'quit'" << RESET << " at any time to exit                         " << YELLOW << "|" << RESET << "\n";
    cout << YELLOW << "  +-------------------------------------------------------------+" << RESET << "\n";
    cout << "\n";
}

// ─── Turn Header ──────────────────────────────────────────────────────────────
void Game::show_turn_header() const {
    string player_name = (current_turn == 'W') ? player1.get_name() : player2.get_name();
    string color_name  = (current_turn == 'W') ? "WHITE" : "BLACK";
    const string& C    = turn_color(current_turn);

    cout << "\n";
    cout << C << "  +-------------------------------------------------------------+" << RESET << "\n";
    cout << C << "  |" << RESET << BOLD;
    if (current_turn == 'W')
        cout << CYAN;
    else
        cout << RED;
    cout << "  [ " << color_name << " TO MOVE ]  " << RESET << "  " << player_name;
    cout << "\n";
    cout << C << "  +-------------------------------------------------------------+" << RESET << "\n";
}

// ─── Game Over Screen — polished, colored, unambiguous ────────────────────────
void Game::show_game_over(char winner) const {
    clear_screen();
    cout << "\n";

    if (winner == 'D') {
        // Stalemate — neutral yellow
        cout << YELLOW << "  +=============================================================+" << RESET << "\n";
        cout << YELLOW << "  |" << RESET << "                                                             " << YELLOW << "|" << RESET << "\n";
        cout << YELLOW << "  |" << RESET << BOLD << "                     G A M E   O V E R                     " << RESET << YELLOW << "|" << RESET << "\n";
        cout << YELLOW << "  |" << RESET << "                                                             " << YELLOW << "|" << RESET << "\n";
        cout << YELLOW << "  +=============================================================+" << RESET << "\n";
        cout << "\n";
        cout << YELLOW << "  +-------------------------------------------------------------+" << RESET << "\n";
        cout << YELLOW << "  |" << RESET << "                                                             " << YELLOW << "|" << RESET << "\n";
        cout << YELLOW << "  |" << RESET << BOLD << "           S T A L E M A T E  —  I T ' S  A  D R A W          " << RESET << YELLOW << "|" << RESET << "\n";
        cout << YELLOW << "  |" << RESET << "              Neither player can make a legal move.          " << YELLOW << "|" << RESET << "\n";
        cout << YELLOW << "  |" << RESET << "                                                             " << YELLOW << "|" << RESET << "\n";
        cout << YELLOW << "  +-------------------------------------------------------------+" << RESET << "\n";
    } else {
        string winner_name  = (winner == 'W') ? player1.get_name() : player2.get_name();
        string loser_name   = (winner == 'W') ? player2.get_name() : player1.get_name();
        string winner_color = (winner == 'W') ? "WHITE" : "BLACK";
        const string& WC    = (winner == 'W') ? CYAN : RED;
        const string& LC    = (winner == 'W') ? RED  : CYAN;

        cout << WC << "  +=============================================================+" << RESET << "\n";
        cout << WC << "  |" << RESET << "                                                             " << WC << "|" << RESET << "\n";
        cout << WC << "  |" << RESET << BOLD << "                     G A M E   O V E R                     " << RESET << WC << "|" << RESET << "\n";
        cout << WC << "  |" << RESET << "                                                             " << WC << "|" << RESET << "\n";
        cout << WC << "  +=============================================================+" << RESET << "\n";
        cout << "\n";
        cout << WC << "  +-------------------------------------------------------------+" << RESET << "\n";
        cout << WC << "  |" << RESET << "                                                             " << WC << "|" << RESET << "\n";

        // Winner line — bold and colored
        cout << WC << "  |" << RESET << "  " << BOLD << WC << "  *** CHECKMATE! ***" << RESET;
        cout << "  " << BOLD << WC << winner_name << " (" << winner_color << ")" << RESET << " wins the game!" << "\n";

        cout << WC << "  |" << RESET << "                                                             " << WC << "|" << RESET << "\n";
        cout << WC << "  |" << RESET << "  " << LC << "  " << loser_name << " has no legal moves remaining." << RESET << "           " << WC << "|" << RESET << "\n";
        cout << WC << "  |" << RESET << "                                                             " << WC << "|" << RESET << "\n";
        cout << WC << "  +-------------------------------------------------------------+" << RESET << "\n";
    }
    cout << "\n";
}

// ─── Constructor ──────────────────────────────────────────────────────────────
Game::Game() : player1("", 'W'), player2("", 'B'), current_turn('W'), game_over(false) {
    show_welcome();

    string name1, name2;
    cout << CYAN << "  >> " << RESET << "Enter White player name: ";
    getline(cin, name1);
    if (name1.empty()) name1 = "Player 1";

    cout << RED  << "  >> " << RESET << "Enter Black player name: ";
    getline(cin, name2);
    if (name2.empty()) name2 = "Player 2";

    player1 = Player(name1, 'W');
    player2 = Player(name2, 'B');

    cout << "\n  " << GREEN << ">> " << RESET << "Let's begin!  "
         << CYAN << BOLD << player1.get_name() << " (White)" << RESET
         << " vs "
         << RED << BOLD << player2.get_name() << " (Black)" << RESET << "\n";
    cout << "\n  Press ENTER to start...";
    cin.get();
}

Game::~Game() {}

// ─── Square Parser ────────────────────────────────────────────────────────────
// Accepts "e2", handles both space-separated and dash-separated input.
bool Game::parse_square(const string& s, int& row, int& col) const {
    try {
        if (s.empty())         throw EmptyMoveException();
        if (s == "quit")       throw QuitGameException();
        if (s.size() < 2)      throw InvalidSquareFormatException(s);

        char file = tolower(s[0]);
        char rank = s[1];

        if (file < 'a' || file > 'h') throw InvalidFileException(file);
        if (rank < '1' || rank > '8') throw InvalidRankException(rank);

        col = file - 'a';
        row = 8 - (rank - '0');
        return true;
    }
    catch (QuitGameException&) { throw; }
    catch (MoveException& e) {
        cerr << "\n  " << YELLOW << "[!] " << RESET << e.what() << "\n";
        return false;
    }
    catch (exception& e) {
        cerr << "\n  " << YELLOW << "[!] " << RESET << "Unexpected error: " << e.what() << "\n";
        return false;
    }
}

// ─── Parse a full move line: "e2 e4" OR "e2-e4" → from_str + to_str ──────────
// Returns true on success, sets from_str and to_str.
bool Game::parse_move_line(const string& line, string& from_str, string& to_str) const {
    if (line.empty()) return false;

    // Support dash separator: replace '-' with ' '
    string cleaned = line;
    for (char& c : cleaned)
        if (c == '-') c = ' ';

    // Tokenize by whitespace
    vector<string> tokens;
    string tok;
    for (size_t i = 0; i <= cleaned.size(); ++i) {
        char c = (i < cleaned.size()) ? cleaned[i] : ' ';
        if (c == ' ' || c == '\t') {
            if (!tok.empty()) { tokens.push_back(tok); tok.clear(); }
        } else {
            tok += c;
        }
    }

    if (tokens.size() < 2) return false;
    from_str = tokens[0];
    to_str   = tokens[1];
    return true;
}

// ─── Main Game Loop ───────────────────────────────────────────────────────────
void Game::run() {
    while (!game_over) {
        try {
            clear_screen();
            show_turn_header();
            board.display(current_turn);   // pass turn for dynamic colors

            bool in_check = board.is_in_check(current_turn);
            bool no_moves = board.has_no_legal_moves(current_turn);

            if (no_moves) {
                char winner = in_check ? ((current_turn == 'W') ? 'B' : 'W') : 'D';
                show_game_over(winner);
                game_over = true;
                break;
            }

            if (in_check) {
                cout << "  " << YELLOW << "[!] CHECK!" << RESET
                     << " Your king is under attack — you must escape!\n\n";
            }

            string whose_turn = (current_turn == 'W')
                ? player1.get_name() : player2.get_name();
            const string& C = turn_color(current_turn);

            cout << "  " << C << ">> " << RESET << whose_turn
                 << ", enter move " << BOLD << "(e.g. e2 e4 or e2-e4)" << RESET
                 << " or 'quit': ";

            // ── Single-line input ────────────────────────────────────────────
            string line;
            getline(cin, line);

            // Trim leading/trailing spaces
            size_t s = line.find_first_not_of(" \t");
            size_t e = line.find_last_not_of(" \t");
            if (s == string::npos) { line = ""; } else { line = line.substr(s, e - s + 1); }

            if (line == "quit") throw QuitGameException();
            if (line.empty()) {
                cout << "\n  " << YELLOW << "[!]" << RESET << " No move entered. Press ENTER to retry...";
                cin.get();
                continue;
            }

            string from_str, to_str;
            if (!parse_move_line(line, from_str, to_str)) {
                cout << "\n  " << YELLOW << "[X]" << RESET
                     << " Could not read two squares from: \"" << line << "\"\n";
                cout << "  Format: " << BOLD << "e2 e4" << RESET << "  or  "
                     << BOLD << "e2-e4" << RESET << "  — Press ENTER to retry...";
                cin.get();
                continue;
            }

            int fr, fc, tr, tc;
            if (!parse_square(from_str, fr, fc)) {
                cout << "\n  " << YELLOW << "[X]" << RESET
                     << " Invalid source square. Press ENTER to retry...";
                cin.get();
                continue;
            }
            if (!parse_square(to_str, tr, tc)) {
                cout << "\n  " << YELLOW << "[X]" << RESET
                     << " Invalid destination square. Press ENTER to retry...";
                cin.get();
                continue;
            }

            if (!board.make_move(fr, fc, tr, tc, current_turn))
                throw IllegalMoveException(from_str, to_str);

            // Confirmation
            string color_name = (current_turn == 'W') ? "White" : "Black";
            cout << "\n  " << GREEN << "[OK]" << RESET << " " << color_name
                 << " moves: " << BOLD << from_str << " → " << to_str << RESET << "\n";

            this_thread::sleep_for(chrono::milliseconds(700));

            current_turn = (current_turn == 'W') ? 'B' : 'W';
        }
        catch (QuitGameException&) {
            clear_screen();
            cout << "\n";
            cout << YELLOW << "  +-------------------------------------------------------------+" << RESET << "\n";
            cout << YELLOW << "  |" << RESET << "              Game ended by player. Thanks for playing!      " << YELLOW << "|" << RESET << "\n";
            cout << YELLOW << "  +-------------------------------------------------------------+" << RESET << "\n\n";
            game_over = true;
            break;
        }
        catch (IllegalMoveException& e) {
            cerr << "\n  " << RED << e.what() << RESET << "\n";
            cout << "  " << YELLOW << "[?]" << RESET
                 << " Tip: check the path is clear and matches piece movement rules.\n";
            cout << "\n  Press ENTER to try again...";
            cin.get();
        }
        catch (MoveException& e) {
            cerr << "\n  " << YELLOW << e.what() << RESET << "\n";
            cout << "\n  Press ENTER to try again...";
            cin.get();
        }
        catch (exception& e) {
            cerr << "\n  " << RED << "[!] Unexpected error: " << e.what() << RESET << "\n";
            cout << "\n  Press ENTER to continue...";
            cin.get();
        }
    }

    // Final board + farewell
    if (game_over) {
        cout << "\n  " << BOLD << ">> Final board position:" << RESET << "\n";
        board.display(current_turn);
        cout << "  " << GREEN << "Thank you for playing!" << RESET << "\n\n";
    }
}
