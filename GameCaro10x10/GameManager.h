// GameManager.h
// [Thành viên 4] Khai báo quản lý trận đấu, Replay

// GameManager.h
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Board.h"
#include "Storage.h"
#include <vector>

struct Move
{
    int row, col;
    char symbol;
};

class GameManager
{
private:
    Board board;
    Storage storage;
    std::vector<Move> history; // Lưu lịch sử trận đấu để phục vụ tính năng Replay

public:
    GameManager() : storage("players_data.txt") {}
    void mainMenu();
    void playPvP();
    void playPvE();
    void saveReplay();
    void watchReplay(); // Tính năng xem lại trận đấu (R3)
};

#endif