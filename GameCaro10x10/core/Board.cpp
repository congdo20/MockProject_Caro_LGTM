#include "Board.h"
#include <iostream>

Board::Board() : size(10), matrix(size, std::vector<char>(size, ' '))
{
}

void Board::reset()
{
    matrix.assign(size, std::vector<char>(size, ' '));
}

void Board::display() const
{
    std::cout << "   ";
    for (int col = 0; col < size; ++col)
    {
        std::cout << (col < 10 ? " " : "") << col << " ";
    }
    std::cout << '\n';

    for (int row = 0; row < size; ++row)
    {
        std::cout << (row < 10 ? " " : "") << row << " ";
        for (int col = 0; col < size; ++col)
        {
            std::cout << " " << (matrix[row][col] == ' ' ? '.' : matrix[row][col]) << " ";
        }
        std::cout << '\n';
    }
}

bool Board::makeMove(int row, int col, char symbol)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false;
    }
    if (matrix[row][col] != ' ')
    {
        return false;
    }
    matrix[row][col] = symbol;
    return true;
}

void Board::setCell(int row, int col, char symbol)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return;
    }
    matrix[row][col] = symbol;
}

char Board::getCell(int row, int col) const
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return ' ';
    }
    return matrix[row][col];
}

static int countDirection(const std::vector<std::vector<char>> &matrix, int row, int col, int dRow, int dCol)
{
    int count = 0;
    int size = static_cast<int>(matrix.size());
    char symbol = matrix[row][col];
    int r = row + dRow;
    int c = col + dCol;

    while (r >= 0 && r < size && c >= 0 && c < size && matrix[r][c] == symbol)
    {
        ++count;
        r += dRow;
        c += dCol;
    }
    return count;
}

bool Board::checkWin(int row, int col) const
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false;
    }
    char symbol = matrix[row][col];
    if (symbol == ' ')
    {
        return false;
    }

    const std::vector<std::vector<char>> directions = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}};

    for (const auto &dir : directions)
    {
        int dRow = dir[0];
        int dCol = dir[1];
        int count = 1 + countDirection(matrix, row, col, dRow, dCol) + countDirection(matrix, row, col, -dRow, -dCol);
        if (count >= 5)
        {
            return true;
        }
    }
    return false;
}

bool Board::checkDraw() const
{
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            if (matrix[row][col] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}
