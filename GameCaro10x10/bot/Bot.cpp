#include "Bot.h"
#include "Minimax.h"
#include <cstdlib>
#include <ctime>
#include <vector>

// Khoi tao Bot voi cap do va ky hieu quan, seed ngau nhien cho moveEasy/moveNormal
Bot::Bot(int lvl, char s): Player("Bot AI", s), level(lvl){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// Cap do Easy: thu thap tat ca o trong va chon ngau nhien mot o
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

// Cap do Normal: lay top 3 nuoc di tot nhat tu Minimax, roi chon theo ty le ngau nhien
std::pair<int, int> Bot::moveNormal(const Board &board)
{
    auto topMoves = Minimax::findTopMoves(board, getSymbol(), 2, 3);
    
    if (topMoves.empty()) {
        return moveEasy(board);
    }
    
    if (topMoves.size() == 1) {
        return topMoves[0].second;
    }

    // Ty le: 50% nuoc tot nhat, 33% nuoc thu 2, 17% nuoc thu 3
    int roll = std::rand() % 6;
    int pick;
    if (roll < 3) {
        pick = 0;
    } else if (roll < 5) {
        pick = 1; 
    } else {
        pick = std::min(2, (int)topMoves.size() - 1); 
    }
    
    return topMoves[pick].second;
}

// Cap do Hard: dung Minimax voi do sau 4 de tim nuoc di tot nhat
std::pair<int, int> Bot::moveHard(const Board &board)
{
    return Minimax::findBestMove(board, getSymbol(), 4);
}

// Phan phoi nuoc di theo cap do da chon khi khoi tao Bot
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
