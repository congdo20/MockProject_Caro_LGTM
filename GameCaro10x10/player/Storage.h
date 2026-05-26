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
    Storage(std::string file);
    bool loadFromFile();
    bool saveToFile() const;
    void updateResult(const std::string &name, const std::string &result);
    PlayerData *searchPlayer(const std::string &name);
    PlayerData *findMatchmaking(const std::string &name);
    void addPlayer(const PlayerData &player);
    const std::vector<PlayerData> &getPlayers() const;
};

#endif
