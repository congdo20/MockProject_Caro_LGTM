#ifndef BOARD_H
#define BOARD_H

#include <vector>

// Lớp Board: quản lý bàn cờ 10x10, lưu trạng thái các ô và kiểm tra thắng/thua/hòa
class Board
{
private:
    int size;                               // kích thước bàn cờ (mặc định 10)
    std::vector<std::vector<char>> matrix;  // ma trận lưu trạng thái từng ô (' ', 'X', 'O')

public:
    Board();                                                // khởi tạo bàn cờ 10x10, tất cả ô trống
    void reset();                                           // đặt lại toàn bộ ô về trống
    void display() const;                                   // in bàn cờ ra màn hình console
    bool makeMove(int row, int col, char symbol);           // đặt quân symbol vào (row, col), trả false nếu ô đã có quân hoặc ngoài biên
    void setCell(int row, int col, char symbol);            // ghi trực tiếp symbol vào ô (row, col), dùng cho AI thử nước đi
    char getCell(int row, int col) const;                   // trả về ký tự tại ô (row, col), trả ' ' nếu ngoài biên
    bool checkWin(int row, int col) const;                  // kiểm tra quân vừa đặt tại (row, col) có tạo thành 5 liên tiếp không
    bool checkDraw() const;                                 // kiểm tra bàn cờ đã đầy (hòa) chưa
    int getSize() const { return size; }                    // trả về kích thước bàn cờ
};

#endif