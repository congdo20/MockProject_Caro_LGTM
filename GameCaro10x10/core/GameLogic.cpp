#include "GameLogic.h"

// Khởi tạo: người đi trước là 'X', reset bàn cờ về trạng thái trống
GameLogic::GameLogic()
    : currentPlayer('X')
{
    board.reset();
}

// Đặt lại toàn bộ trạng thái về đầu ván: xóa bàn cờ, xóa lịch sử, về lượt 'X'
void GameLogic::reset()
{
    board.reset();
    history.clear();
    currentPlayer = 'X';
}

// Thực hiện nước đi tại (row, col) cho người chơi hiện tại
// Trả về false nếu ô không hợp lệ hoặc đã có quân
bool GameLogic::makeMove(int row, int col)
{
    if (!board.makeMove(row, col, currentPlayer)) {
        return false; // nước đi không hợp lệ
    }
    history.emplace_back(row, col, currentPlayer); // ghi vào lịch sử
    return true;
}

// Kiểm tra nước vừa đặt tại (row, col) có tạo thành 5 liên tiếp không
bool GameLogic::isWinningMove(int row, int col) const
{
    return board.checkWin(row, col);
}

// Kiểm tra bàn cờ đã hòa (đầy mà không ai thắng)
bool GameLogic::isDraw() const
{
    return board.checkDraw();
}

// Chuyển lượt: 'X' → 'O' hoặc 'O' → 'X'
void GameLogic::switchPlayer()
{
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Trả về ký hiệu người chơi đang đến lượt
char GameLogic::getCurrentPlayer() const
{
    return currentPlayer;
}

// Trả về tham chiếu const đến bàn cờ hiện tại
const Board &GameLogic::getBoard() const
{
    return board;
}

// Trả về tham chiếu const đến lịch sử toàn bộ nước đi trong ván
const std::vector<Move> &GameLogic::getHistory() const
{
    return history;
}
