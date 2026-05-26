#ifndef EVALUATION_H
#define EVALUATION_H

#include "../core/Board.h"

class Evaluation
{
public:
    static int evaluate(const Board &board, char symbol);
};

#endif
