#include "GameLogic.h"

GameLogic::GameLogic()
    : currentPlayer('X')
{
    board.reset();
}

void GameLogic::reset()
{
    board.reset();
    history.clear();
    currentPlayer = 'X';
}

bool GameLogic::makeMove(int row, int col)
{
    if (!board.makeMove(row, col, currentPlayer)) {
        return false;
    }
    history.emplace_back(row, col, currentPlayer);
    return true;
}

bool GameLogic::isWinningMove(int row, int col) const
{
    return board.checkWin(row, col);
}

bool GameLogic::isDraw() const
{
    return board.checkDraw();
}

void GameLogic::switchPlayer()
{
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

char GameLogic::getCurrentPlayer() const
{
    return currentPlayer;
}

const Board &GameLogic::getBoard() const
{
    return board;
}

const std::vector<Move> &GameLogic::getHistory() const
{
    return history;
}
