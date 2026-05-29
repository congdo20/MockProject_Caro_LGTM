#include "Bot.h"
#include "Minimax.h"
#include <cstdlib>
#include <ctime>
#include <vector>

Bot::Bot(int lvl, char s): Player("Bot AI", s), level(lvl){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

std::pair<int, int> Bot::moveEasy(const Board &board)
{
    std::vector<std::pair<int, int>> emptyCells;
    for (int row = 0; row < board.getSize(); ++row) {
        for (int col = 0; col < board.getSize(); ++col){
            if (board.getCell(row, col) == ' ') {
                emptyCells.push_back({row, col});
            }
        }
    }
    
    if (!emptyCells.empty()) {
        int randomIndex = std::rand() % emptyCells.size();
        return emptyCells[randomIndex];
    }
    
    return {0, 0};
}

std::pair<int, int> Bot::moveNormal(const Board &board)
{
    if (std::rand() % 100 < 30) {
        return moveEasy(board);
    }
    
    return Minimax::findBestMove(board, getSymbol(), 3);
}

std::pair<int, int> Bot::moveHard(const Board &board)
{
    return Minimax::findBestMove(board, getSymbol(), 4);
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
