#include "PlayerManager.h"
#include <iostream>

PlayerManager::PlayerManager(const std::string &filename)
    : storage(filename)
{
}

bool PlayerManager::load()
{
    return storage.loadFromFile();
}

bool PlayerManager::save() const
{
    return storage.saveToFile();
}

void PlayerManager::registerPlayer(const std::string &name)
{
    if (!storage.searchPlayer(name))
    {
        PlayerData player;
        player.name = name;
        player.wins = 0;
        player.losses = 0;
        player.draws = 0;
        storage.addPlayer(player);
    }
}

void PlayerManager::updateResult(const std::string &name, const std::string &result)
{
    storage.updateResult(name, result);
}

PlayerData *PlayerManager::findPlayer(const std::string &name)
{
    return storage.searchPlayer(name);
}

void PlayerManager::printPlayers() const
{
    const auto &players = storage.getPlayers();
    if (players.empty())
    {
        std::cout << "Chua co du lieu nguoi choi.\n";
        return;
    }
    std::cout << "Danh sach nguoi choi:\n";
    for (const auto &player : players)
    {
        std::cout << "- " << player.name << ": " << player.wins << "W " << player.losses << "L " << player.draws << "D\n";
    }
}
