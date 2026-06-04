#ifndef BOARD_H
#define BOARD_H

#include <vector>

// Lop Board: quan ly ban co 10x10, luu trang thai o va kiem tra thang/thua/hoa
class Board
{
private:
    int size;                               // kich thuoc ban co (mac dinh 10)
    std::vector<std::vector<char>> matrix;  // ma tran luu trang thai tung o (' ', 'X', 'O')

public:
    Board();                                                // khoi tao ban co 10x10, tat ca o trong
    void reset();                                           // dat lai toan bo o ve trong
    void display() const;                                   // in ban co ra man hinh console
    bool makeMove(int row, int col, char symbol);           // dat quan symbol vao (row, col), tra false neu o da co quan hoac ngoai bien
    void setCell(int row, int col, char symbol);            // ghi truc tiep symbol vao o (row, col), dung cho AI thu nuoc di
    char getCell(int row, int col) const;                   // tra ve ky tu tai o (row, col), tra ' ' neu ngoai bien
    bool checkWin(int row, int col) const;                  // kiem tra quan vua dat tai (row, col) co tao thanh 5 lien tiep khong
    bool checkDraw() const;                                 // kiem tra ban co da day (hoa) chua
    int getSize() const { return size; }                    // tra ve kich thuoc ban co
};

#endif
