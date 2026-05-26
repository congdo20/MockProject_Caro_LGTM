#ifndef MINIMAX_H
#define MINIMAX_H

#include "../core/Board.h"
#include <utility>

class Minimax
{
public:
    static std::pair<int, int> findBestMove(const Board &board, char symbol, int depth = 2);
};

#endif
