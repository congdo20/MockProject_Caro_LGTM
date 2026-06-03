#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Board.h"
#include "Move.h"
#include <vector>

// Lớp GameLogic: điều phối luật chơi, quản lý lượt đi, lịch sử nước đi và trạng thái thắng/hòa
class GameLogic
{
private:
    Board board;                    // bàn cờ hiện tại
    char currentPlayer;             // ký hiệu người chơi đang đến lượt ('X' hoặc 'O')
    std::vector<Move> history;      // lịch sử các nước đi đã thực hiện trong ván

public:
    GameLogic();                                            // khởi tạo: reset bàn cờ, đặt người đi trước là 'X'
    void reset();                                           // đặt lại toàn bộ trạng thái về đầu ván mới
    bool makeMove(int row, int col);                        // thực hiện nước đi tại (row, col) cho người chơi hiện tại, trả false nếu không hợp lệ
    bool isWinningMove(int row, int col) const;             // kiểm tra nước vừa đặt tại (row, col) có thắng không
    bool isDraw() const;                                    // kiểm tra bàn cờ đã hòa (đầy mà chưa có người thắng)
    void switchPlayer();                                    // chuyển lượt sang người chơi kia
    char getCurrentPlayer() const;                          // trả về ký hiệu người chơi đang đến lượt
    const Board &getBoard() const;                          // trả về tham chiếu const đến bàn cờ hiện tại
    const std::vector<Move> &getHistory() const;            // trả về tham chiếu const đến lịch sử nước đi
};

#endif
