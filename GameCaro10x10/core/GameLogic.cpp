#include "GameLogic.h"

// Khoi tao: nguoi di truoc la 'X', reset ban co ve trang thai trong
GameLogic::GameLogic()
    : currentPlayer('X')
{
    board.reset();
}

// Dat lai toan bo trang thai ve dau van: xoa ban co, xoa lich su, ve luot 'X'
void GameLogic::reset()
{
    board.reset();
    history.clear();
    currentPlayer = 'X';
}

// Thuc hien nuoc di tai (row, col) cho nguoi choi hien tai
// Tra ve false neu o khong hop le hoac da co quan
bool GameLogic::makeMove(int row, int col)
{
    if (!board.makeMove(row, col, currentPlayer)) {
        return false; // nuoc di khong hop le
    }
    history.emplace_back(row, col, currentPlayer); // ghi vao lich su
    return true;
}

// Kiem tra nuoc vua dat tai (row, col) co tao thanh 5 lien tiep khong
bool GameLogic::isWinningMove(int row, int col) const
{
    return board.checkWin(row, col);
}

// Kiem tra ban co da hoa (day ma khong ai thang)
bool GameLogic::isDraw() const
{
    return board.checkDraw();
}

// Chuyen luot: 'X' -> 'O' hoac 'O' -> 'X'
void GameLogic::switchPlayer()
{
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Tra ve ky hieu nguoi choi dang den luot
char GameLogic::getCurrentPlayer() const
{
    return currentPlayer;
}

// Tra ve tham chieu const den ban co hien tai
const Board &GameLogic::getBoard() const
{
    return board;
}

// Tra ve tham chieu const den lich su toan bo nuoc di trong van
const std::vector<Move> &GameLogic::getHistory() const
{
    return history;
}
