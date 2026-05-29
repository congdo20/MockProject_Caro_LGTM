#ifndef BOT_H
#define BOT_H

#include "../player/Player.h"
#include "../core/Board.h"
#include <utility>

class Bot : public Player
{
private:
    int level; 

    std::pair<int, int> moveEasy(const Board &board);
    std::pair<int, int> moveNormal(const Board &board);
    std::pair<int, int> moveHard(const Board &board);

public:
    Bot(int lvl, char s);
    std::pair<int, int> getNextMove(const Board &board);
};

#endif
