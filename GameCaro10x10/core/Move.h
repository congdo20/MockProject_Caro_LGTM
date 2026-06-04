#ifndef MOVE_H
#define MOVE_H

// Struct Move: luu thong tin mot nuoc di gom toa do hang, cot va ky hieu quan dat
struct Move
{
    int row;     // hang cua nuoc di (0-indexed)
    int col;     // cot cua nuoc di (0-indexed)
    char symbol; // ky hieu quan dat ('X' hoac 'O')

    // Constructor mac dinh: khoi tao toa do (0,0) va ky hieu ' '
    Move(int r = 0, int c = 0, char s = ' ') : row(r), col(c), symbol(s) {}
};

#endif
