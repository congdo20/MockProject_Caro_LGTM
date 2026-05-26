// Board.cpp
// [Thành viên 1] Định nghĩa logic, vẽ, check thắng

// Board.cpp
#include "Board.h"
#include <iostream>

Board::Board() : size(10)
{
    reset();
}

void Board::reset()
{
    matrix.assign(size, std::vector<char>(size, ' '));
}

void Board::display() const
{
    // [Thành viên 1]: Viết code vẽ bàn cờ Console đẹp mắt ở đây
    std::cout << "--- BAN CO CARO 10x10 ---\n";
}

bool Board::makeMove(int row, int col, char symbol)
{
    // [Thành viên 1]: Kiểm tra tọa độ hợp lệ và điền symbol ('X' hoặc 'O')
    return false;
}

bool Board::checkWin(int row, int col) const
{
    // [Thành viên 1]: Kiểm tra 5 ô liên tiếp (Ngang, Dọc, Chéo) từ vị trí vừa đánh
    return false;
}

bool Board::checkDraw() const
{
    // [Thành viên 1]: Kiểm tra hết ô trống mà chưa ai thắng
    return false;
}