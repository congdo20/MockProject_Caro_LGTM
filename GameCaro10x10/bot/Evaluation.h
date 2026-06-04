#ifndef EVALUATION_H
#define EVALUATION_H

#include "../core/Board.h"

// Lop Evaluation: tinh diem the cho ban co tu goc nhin mot ky hieu quan
class Evaluation
{
public:
    static int evaluate(const Board &board, char symbol);
};

#endif
