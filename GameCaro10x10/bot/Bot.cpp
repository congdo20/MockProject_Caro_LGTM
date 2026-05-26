#include "Bot.h"
#include "Minimax.h"
#include <cstdlib>
#include <ctime>

Bot::Bot(int lvl, char s)
    : Player("Bot AI", s), level(lvl)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

std::pair<int, int> Bot::moveEasy(const Board &board)
{
    for (int row = 0; row < board.getSize(); ++row) {
        for (int col = 0; col < board.getSize(); ++col) {
            if (board.getCell(row, col) == ' ') {
                return {row, col};
            }
        }
    }
    return {0, 0};
}

std::pair<int, int> Bot::moveNormal(const Board &board)
{
    auto candidate = moveEasy(board);
    if (candidate.first == 0 && candidate.second == 0) {
        return candidate;
    }
    return {board.getSize() / 2, board.getSize() / 2};
}

std::pair<int, int> Bot::moveHard(const Board &board)
{
    return Minimax::findBestMove(board, getSymbol(), 2);
}

std::pair<int, int> Bot::getNextMove(const Board &board)
{
    if (level == 2) {
        return moveNormal(board);
    }
    if (level == 3) {
        return moveHard(board);
    }
    return moveEasy(board);
}
