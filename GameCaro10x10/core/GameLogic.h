#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Board.h"
#include "Move.h"
#include <vector>

// Lop GameLogic: dieu phoi luat choi, quan ly luot di, lich su nuoc di va trang thai thang/hoa
class GameLogic
{
private:
    Board board;                    // ban co hien tai
    char currentPlayer;             // ky hieu nguoi choi dang den luot ('X' hoac 'O')
    std::vector<Move> history;      // lich su cac nuoc di da thuc hien trong van

public:
    GameLogic();                                            // khoi tao: reset ban co, dat nguoi di truoc la 'X'
    void reset();                                           // dat lai toan bo trang thai ve dau van moi
    bool makeMove(int row, int col);                        // thuc hien nuoc di tai (row, col) cho nguoi choi hien tai, tra false neu khong hop le
    bool isWinningMove(int row, int col) const;             // kiem tra nuoc vua dat tai (row, col) co thang khong
    bool isDraw() const;                                    // kiem tra ban co da hoa (day ma chua co nguoi thang)
    void switchPlayer();                                    // chuyen luot sang nguoi choi kia
    char getCurrentPlayer() const;                          // tra ve ky hieu nguoi choi dang den luot
    const Board &getBoard() const;                          // tra ve tham chieu const den ban co hien tai
    const std::vector<Move> &getHistory() const;            // tra ve tham chieu const den lich su nuoc di
};

#endif
