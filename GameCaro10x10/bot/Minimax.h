#ifndef MINIMAX_H
#define MINIMAX_H

#include "../core/Board.h"
#include <utility>
#include <vector>

class Minimax
{
public:
    static std::pair<int, int> findBestMove(const Board &board, char symbol, int depth = 2);
    static std::vector<std::pair<int, std::pair<int, int>>> findTopMoves(const Board &board, char symbol, int depth, int topN);
};

#endif
