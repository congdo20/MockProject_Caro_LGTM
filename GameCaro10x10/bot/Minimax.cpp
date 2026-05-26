#include "Minimax.h"
#include "Evaluation.h"
#include <algorithm>

static int evaluateBoard(const Board &board, char symbol)
{
    return Evaluation::evaluate(board, symbol);
}

static int minimax(Board &board, int depth, bool maximizingPlayer, char playerSymbol, char opponentSymbol)
{
    if (depth == 0)
    {
        return evaluateBoard(board, playerSymbol);
    }

    int bestValue = maximizingPlayer ? -100000 : 100000;
    for (int row = 0; row < board.getSize(); ++row)
    {
        for (int col = 0; col < board.getSize(); ++col)
        {
            if (board.getCell(row, col) != ' ')
            {
                continue;
            }
            char symbol = maximizingPlayer ? playerSymbol : opponentSymbol;
            board.setCell(row, col, symbol);
            int value = minimax(board, depth - 1, !maximizingPlayer, playerSymbol, opponentSymbol);
            board.setCell(row, col, ' ');
            if (maximizingPlayer)
            {
                bestValue = std::max(bestValue, value);
            }
            else
            {
                bestValue = std::min(bestValue, value);
            }
        }
    }
    return bestValue;
}

std::pair<int, int> Minimax::findBestMove(const Board &board, char symbol, int depth)
{
    Board copy = board;
    char opponent = (symbol == 'X') ? 'O' : 'X';
    int bestScore = -100000;
    std::pair<int, int> bestMove = {0, 0};

    for (int row = 0; row < copy.getSize(); ++row)
    {
        for (int col = 0; col < copy.getSize(); ++col)
        {
            if (copy.getCell(row, col) != ' ')
            {
                continue;
            }
            copy.makeMove(row, col, symbol);
            int score = minimax(copy, depth - 1, false, symbol, opponent);
            copy.setCell(row, col, ' ');
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = {row, col};
            }
        }
    }
    return bestMove;
}
