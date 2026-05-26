#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Board.h"
#include "Move.h"
#include <vector>

class GameLogic
{
private:
    Board board;
    char currentPlayer;
    std::vector<Move> history;

public:
    GameLogic();
    void reset();
    bool makeMove(int row, int col);
    bool isWinningMove(int row, int col) const;
    bool isDraw() const;
    void switchPlayer();
    char getCurrentPlayer() const;
    const Board &getBoard() const;
    const std::vector<Move> &getHistory() const;
};

#endif
