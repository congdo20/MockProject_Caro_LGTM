#ifndef MOVE_H
#define MOVE_H

struct Move
{
    int row;
    int col;
    char symbol;

    Move(int r = 0, int c = 0, char s = ' ') : row(r), col(c), symbol(s) {}
};

#endif
