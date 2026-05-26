#ifndef REPLAY_H
#define REPLAY_H

#include "../core/Move.h"
#include <string>
#include <vector>

class Replay
{
private:
    std::vector<Move> moves;
    std::string name;

public:
    Replay() = default;
    explicit Replay(const std::string &title);

    void addMove(int row, int col, char symbol);
    const std::vector<Move> &getMoves() const;
    const std::string &getName() const;
    void print() const;
};

#endif
