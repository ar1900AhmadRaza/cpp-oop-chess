#pragma once
#include <iostream>
#include <string>
using namespace std;
class Player 
{
    string name;
    char  color;    // 'W' or 'B'
public:
    Player(string name, char color);
    string get_name()  const;
    char   get_color() const;
    bool get_input(string& from_str, string& to_str) const;
};
