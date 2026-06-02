// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
protected:
    std::string name;
    char symbol;

public:
    Player(std::string n, char s) : name(n), symbol(s) {}
    virtual ~Player() {}
    std::string getName() const { return name; }
    char getSymbol() const { return symbol; }
};

#endif