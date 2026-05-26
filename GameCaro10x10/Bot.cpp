// Bot.cpp
// [Thành viên 2] Định nghĩa Easy, Normal, Hard (Minimax)

// Bot.cpp
#include "Bot.h"

std::pair<int, int> Bot::getNextMove(const Board &board)
{
    if (level == 1)
        return moveEasy(board);
    if (level == 2)
        return moveNormal(board);
    return moveHard(board);
}

std::pair<int, int> Bot::moveEasy(const Board &board)
{
    // [Thành viên 2]: Code nước đi ngẫu nhiên
    return {0, 0};
}

std::pair<int, int> Bot::moveNormal(const Board &board)
{
    // [Thành viên 2]: Code nước đi tìm điểm cao cơ bản
    return {0, 0};
}

std::pair<int, int> Bot::moveHard(const Board &board)
{
    // [Thành viên 2]: Cài đặt thuật toán Minimax ở đây
    return {0, 0};
}