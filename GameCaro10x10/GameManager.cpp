// GameManager.cpp
// [Thành viên 4] Định nghĩa vòng lặp game, Replay

// GameManager.cpp
#include "GameManager.h"
#include "Bot.h"
#include <iostream>

void GameManager::mainMenu()
{
    // [Thành viên 4]: Thiết kế giao diện Menu chính bằng console
    std::cout << "1. Play Player vs Player\n2. Play vs Bot\n3. Watch Replay\n4. Exit\n";
}

void GameManager::playPvP()
{
    // [Thành viên 4]: Điều phối vòng lặp game Player 1 đánh -> Board lưu -> Check Win -> Player 2 đánh
}

void GameManager::watchReplay()
{
    // [Thành viên 4]: Đọc dữ liệu từ vector `history` và dựng lại trận đấu từng bước một
}