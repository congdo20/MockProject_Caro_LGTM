// Storage.h
// [Thành viên 3] Khai báo đọc/ghi file, tìm kiếm

// Storage.h
#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

struct PlayerData
{
    std::string name;
    int wins = 0;
    int losses = 0;
    int draws = 0;
};

class Storage
{
private:
    std::string filename;
    std::vector<PlayerData> players;

public:
    Storage(std::string file) : filename(file) {}
    bool loadFromFile();
    bool saveToFile();
    void updateResult(std::string name, std::string result); // result: "win", "lose", "draw"
    PlayerData *searchPlayer(std::string name);
    PlayerData *findMatchmaking(std::string name); // Tìm đối thủ tương đương trình độ
};

#endif