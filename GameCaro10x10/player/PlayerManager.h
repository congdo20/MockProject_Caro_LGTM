#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"
#include "Storage.h"
#include <string>

// Lop PlayerManager: quan ly dang ky, cap nhat ket qua va tim kiem nguoi choi
class PlayerManager
{
private:
    Storage storage;

public:
    PlayerManager(const std::string &filename = "data/players.txt");
    bool load();
    bool save() const;
    void registerPlayer(const std::string &name);                    // them nguoi choi neu chua ton tai
    void updateResult(const std::string &name, const std::string &result); // result: "win", "lose", "draw"
    PlayerData *findPlayer(const std::string &name);
    void printPlayers() const;
};

#endif
