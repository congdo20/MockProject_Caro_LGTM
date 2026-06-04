// Lop co so Player: luu ten va ky hieu quan (X hoac O)

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
protected:
    std::string name;  // ten nguoi choi hoac "Bot AI"
    char symbol;       // ky hieu quan: 'X' hoac 'O'

public:
    Player(std::string n, char s) : name(n), symbol(s) {}
    virtual ~Player() {}
    std::string getName() const { return name; }
    char getSymbol() const { return symbol; }
};

#endif
