#include "Board.h"
#include <iomanip>
#include <iostream>

// Khởi tạo bàn cờ 10x10, tất cả ô mang giá trị ' ' (trống)
Board::Board() : size(10), matrix(size, std::vector<char>(size, ' '))
{
}

// Đặt lại toàn bộ ô về trống, dùng khi bắt đầu ván mới
void Board::reset()
{
    matrix.assign(size, std::vector<char>(size, ' '));
}

// In bàn cờ ra console theo dạng lưới có nhãn hàng/cột
void Board::display() const
{
    // In nhãn cột
    std::cout << "    ";
    for (int col = 0; col < size; ++col)
    {
        std::cout << col << "   ";
    }
    std::cout << '\n';

    // In đường kẻ ngang phân cách đầu bảng
    std::cout << "  |";
    for (int col = 0; col < size; ++col)
    {
        std::cout << "---|";
    }
    std::cout << '\n';

    // In từng hàng cùng nhãn hàng và đường kẻ ngang phân cách
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

    // In viền dưới bàn cờ
    std::cout << "   +";
    for (int col = 0; col < size; ++col)
    {
        std::cout << "---+";
    }
    std::cout << '\n';
}

// Đặt quân symbol vào ô (row, col)
// Trả về false nếu tọa độ ngoài biên hoặc ô đã có quân, true nếu thành công
bool Board::makeMove(int row, int col, char symbol)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false; // tọa độ ngoài biên
    }
    if (matrix[row][col] != ' ')
    {
        return false; // ô đã có quân
    }
    matrix[row][col] = symbol;
    return true;
}

// Ghi trực tiếp symbol vào ô (row, col) không kiểm tra ô trống hay chưa
// Dùng nội bộ cho thuật toán AI thử/rút nước đi
void Board::setCell(int row, int col, char symbol)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return; // bỏ qua nếu ngoài biên
    }
    matrix[row][col] = symbol;
}

// Trả về ký tự tại ô (row, col), trả ' ' nếu tọa độ ngoài biên
char Board::getCell(int row, int col) const
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return ' ';
    }
    return matrix[row][col];
}

// Hàm nội bộ: đếm số quân liên tiếp cùng loại tính từ (row, col) theo hướng (dRow, dCol)
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

// Kiểm tra quân vừa đặt tại (row, col) có tạo thành chuỗi 5 liên tiếp không
// Kiểm tra 4 hướng: ngang, dọc, chéo chính, chéo phụ
bool Board::checkWin(int row, int col) const
{
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false;
    }
    char symbol = matrix[row][col];
    if (symbol == ' ')
    {
        return false; // ô trống không thể thắng
    }

    // Các cặp hướng: (ngang), (dọc), (chéo chính), (chéo phụ)
    const std::vector<std::vector<char>> directions = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}};

    for (const auto &dir : directions)
    {
        int dRow = dir[0];
        int dCol = dir[1];
        // Đếm tổng quân liên tiếp theo hai chiều của hướng hiện tại, cộng thêm 1 cho ô hiện tại
        int count = 1 + countDirection(matrix, row, col, dRow, dCol) + countDirection(matrix, row, col, -dRow, -dCol);
        if (count >= 5)
        {
            return true; // thắng nếu đủ 5 quân liên tiếp
        }
    }
    return false;
}

// Kiểm tra bàn cờ đã đầy chưa (không còn ô trống → hòa)
bool Board::checkDraw() const
{
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            if (matrix[row][col] == ' ')
            {
                return false; // còn ô trống, chưa hòa
            }
        }
    }
    return true; // toàn bộ ô đã có quân
}
