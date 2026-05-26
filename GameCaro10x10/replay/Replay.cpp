#include "Replay.h"
#include <iostream>

Replay::Replay(const std::string &title)
    : name(title)
{
}

void Replay::addMove(int row, int col, char symbol)
{
    moves.emplace_back(row, col, symbol);
}

const std::vector<Move> &Replay::getMoves() const
{
    return moves;
}

const std::string &Replay::getName() const
{
    return name;
}

void Replay::print() const
{
    std::cout << "Replay: " << name << "\n";
    for (size_t index = 0; index < moves.size(); ++index) {
        const Move &move = moves[index];
        std::cout << index + 1 << ". " << move.symbol << " -> (" << move.row << ", " << move.col << ")\n";
    }
}
