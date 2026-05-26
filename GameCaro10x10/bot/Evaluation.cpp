#include "Evaluation.h"

static int scoreLine(int count, int openEnds)
{
    if (count >= 5) {
        return 10000;
    }
    if (count == 4 && openEnds == 2) {
        return 1000;
    }
    if (count == 4 && openEnds == 1) {
        return 100;
    }
    if (count == 3 && openEnds == 2) {
        return 100;
    }
    if (count == 3 && openEnds == 1) {
        return 10;
    }
    return count * 2;
}

int Evaluation::evaluate(const Board &board, char symbol)
{
    char opponent = (symbol == 'X') ? 'O' : 'X';
    int score = 0;
    int size = board.getSize();

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (board.getCell(row, col) != symbol) {
                continue;
            }
            score += 1;
        }
    }

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            if (board.getCell(row, col) == opponent) {
                score -= 1;
            }
        }
    }

    return score;
}
