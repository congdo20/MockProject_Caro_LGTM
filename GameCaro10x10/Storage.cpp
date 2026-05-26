// Storage.cpp
// [Thành viên 3] Định nghĩa I/O Stream, Matchmaking

// Storage.cpp
#include "Storage.h"
#include <fstream>
#include <iostream>

bool Storage::loadFromFile()
{
    // [Thành viên 3]: Sử dụng ifstream đọc file .txt/.ini, xử lý Exception Handling nếu file lỗi
    return true;
}

bool Storage::saveToFile()
{
    // [Thành viên 3]: Sử dụng ofstream ghi đè dữ liệu mới vào file
    return true;
}

PlayerData *Storage::searchPlayer(std::string name)
{
    // [Thành viên 3]: Tìm kiếm tuyến tính hoặc nhị phân trong vector players
    return nullptr;
}

PlayerData *Storage::findMatchmaking(std::string name)
{
    // [Thành viên 3]: Tính tỷ lệ thắng/thua để tìm người có tỷ lệ gần nhất
    return nullptr;
}