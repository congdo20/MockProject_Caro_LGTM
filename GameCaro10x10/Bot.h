// Bot.h
// [Thành viên 2] Khai báo thuật toán AI

// Bot.h
#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include "Board.h"

class Bot : public Player
{
private:
    int level; // 1: Easy, 2: Normal, 3: Hard

    std::pair<int, int> moveEasy(const Board &board);
    std::pair<int, int> moveNormal(const Board &board);
    std::pair<int, int> moveHard(const Board &board); // Áp dụng Minimax

public:
    Bot(int lvl, char s) : Player("Bot AI", s), level(lvl) {}
    std::pair<int, int> getNextMove(const Board &board);
};

#endif