#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"
#include "Storage.h"
#include <string>

class PlayerManager
{
private:
    Storage storage;

public:
    PlayerManager(const std::string &filename = "data/players.txt");
    bool load();
    bool save() const;
    void registerPlayer(const std::string &name);
    void updateResult(const std::string &name, const std::string &result);
    PlayerData *findPlayer(const std::string &name);
    void printPlayers() const;
};

#endif
