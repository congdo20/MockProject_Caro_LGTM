#ifndef MOVE_H
#define MOVE_H

// Struct Move: lưu thông tin một nước đi gồm tọa độ hàng, cột và ký hiệu quân đặt
struct Move
{
    int row;    // hàng của nước đi (0-indexed)
    int col;    // cột của nước đi (0-indexed)
    char symbol; // ký hiệu quân đặt ('X' hoặc 'O')

    // Constructor mặc định: khởi tạo tọa độ (0,0) và ký hiệu ' '
    Move(int r = 0, int c = 0, char s = ' ') : row(r), col(c), symbol(s) {}
};

#endif
