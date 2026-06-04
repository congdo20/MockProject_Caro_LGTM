#include "Board.h"
#include <iomanip>
#include <iostream>

// Khoi tao ban co 10x10, tat ca o mang gia tri ' ' (trong)
Board::Board() : size(10), matrix(size, std::vector<char>(size, ' '))
{
}

// Dat lai toan bo o ve trong, dung khi bat dau van moi
void Board::reset()
{
    matrix.assign(size, std::vector<char>(size, ' '));
}

// In ban co ra console theo dang luoi co nhan hang/cot
void Board::display() const
{
    // In nhan cot
    std::cout << "    ";
    for (int col = 0; col < size; ++col)
    {
        std::cout << col << "   ";
    }
    std::cout << '\n';

    // In duong ke ngang phan cach dau bang
    std::cout << "  |";
    for (int col = 0; col < size; ++col)
    {
        std::cout << "---|";
    }
    std::cout << '\n';

    // In tung hang cung nhan hang va duong ke ngang phan cach
    for (int row = 0; row < size; ++row)
    {
        std::cout << row << " |";
        for (int col = 0; col < size; ++col)
        {
            std::cout << " " << matrix[row][col] << " |";
        }
        std::cout << '\n';

        std::cout << "  |";
        for (int col = 0; col < size; ++col)
        {
            std::cout << "---|";
        }
        std::cout << '\n';
    }

    // In vien duoi ban co
    std::cout << "   +";
    for (int col = 0; col < size; ++col)
    {
        std::cout << "---+";
    }
    std::cout << '\n';
}

// Dat quan symbol vao o (row, col)
// Tra ve false neu toa do ngoai bien hoac o da co quan, true neu thanh cong
bool Board::makeMove(int row, int col, char symbol)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false; // toa do ngoai bien
    }
    if (matrix[row][col] != ' ')
    {
        return false; // o da co quan
    }
    matrix[row][col] = symbol;
    return true;
}

// Ghi truc tiep symbol vao o (row, col) khong kiem tra o trong hay chua
// Dung noi bo cho thuat toan AI thu/rut nuoc di
void Board::setCell(int row, int col, char symbol)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return; // bo qua neu ngoai bien
    }
    matrix[row][col] = symbol;
}

// Tra ve ky tu tai o (row, col), tra ' ' neu toa do ngoai bien
char Board::getCell(int row, int col) const
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return ' ';
    }
    return matrix[row][col];
}

// Ham noi bo: dem so quan lien tiep cung loai tinh tu (row, col) theo huong (dRow, dCol)
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

// Kiem tra quan vua dat tai (row, col) co tao thanh chuoi 5 lien tiep khong
// Kiem tra 4 huong: ngang, doc, cheo chinh, cheo phu
bool Board::checkWin(int row, int col) const
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false;
    }
    char symbol = matrix[row][col];
    if (symbol == ' ')
    {
        return false; // o trong khong the thang
    }

    // Cac cap huong: (ngang), (doc), (cheo chinh), (cheo phu)
    const std::vector<std::vector<char>> directions = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}};

    for (const auto &dir : directions)
    {
        int dRow = dir[0];
        int dCol = dir[1];
        // Dem tong quan lien tiep theo hai chieu cua huong hien tai, cong them 1 cho o hien tai
        int count = 1 + countDirection(matrix, row, col, dRow, dCol) + countDirection(matrix, row, col, -dRow, -dCol);
        if (count >= 5)
        {
            return true; // thang neu du 5 quan lien tiep
        }
    }
    return false;
}

// Kiem tra ban co da day chua (khong con o trong -> hoa)
bool Board::checkDraw() const
{
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            if (matrix[row][col] == ' ')
            {
                return false; // con o trong, chua hoa
            }
        }
    }
    return true; // toan bo o da co quan
}
