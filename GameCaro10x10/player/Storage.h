#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>

// Cau truc luu thong ke mot nguoi choi
struct PlayerData
{
    std::string name;
    int wins = 0;
    int losses = 0;
    int draws = 0;
};

// Lop Storage: doc/ghi danh sach nguoi choi tu file van ban
class Storage
{
private:
    std::string filename;
    std::vector<PlayerData> players;

public:
    Storage(std::string file);
    bool loadFromFile();
    bool saveToFile() const;
    void updateResult(const std::string &name, const std::string &result);
    PlayerData *searchPlayer(const std::string &name);
    PlayerData *findMatchmaking(const std::string &name); // tim doi thu co wins gan nhat
    void addPlayer(const PlayerData &player);
    const std::vector<PlayerData> &getPlayers() const;
};

#endif
