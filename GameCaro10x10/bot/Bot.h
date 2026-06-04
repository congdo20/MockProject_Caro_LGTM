#ifndef BOT_H
#define BOT_H

#include "../player/Player.h"
#include "../core/Board.h"
#include <utility>

// Lop Bot: ke thua Player, chon nuoc di theo cap do kho (Easy/Normal/Hard)
class Bot : public Player
{
private:
    int level; // cap do: 1-Easy, 2-Normal, 3-Hard

    std::pair<int, int> moveEasy(const Board &board);   // di ngau nhien vao o trong
    std::pair<int, int> moveNormal(const Board &board); // chon tu top nuoc di Minimax, co yeu to ngau nhien
    std::pair<int, int> moveHard(const Board &board);   // dung Minimax sau voi do sau lon

public:
    Bot(int lvl, char s);
    std::pair<int, int> getNextMove(const Board &board); // tra ve (hang, cot) cho luot Bot
};

#endif
