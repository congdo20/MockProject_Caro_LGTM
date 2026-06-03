// Board.h

// Board.h
#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
private:
    int size;
    std::vector<std::vector<char>> matrix;

public:
    Board();
    void reset();
    void display() const;
    bool makeMove(int row, int col, char symbol);
    void setCell(int row, int col, char symbol);
    char getCell(int row, int col) const;
    bool checkWin(int row, int col) const;
    bool checkDraw() const;
    int getSize() const { return size; }
};

#endif