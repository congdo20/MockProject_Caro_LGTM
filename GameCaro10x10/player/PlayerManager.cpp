#include "PlayerManager.h"
#include <algorithm>
#include <iostream>

// Gan file luu tru danh sach nguoi choi
PlayerManager::PlayerManager(const std::string &filename)
    : storage(filename)
{
}

// Nap du lieu nguoi choi tu file
bool PlayerManager::load()
{
    return storage.loadFromFile();
}

// Ghi du lieu nguoi choi ra file
bool PlayerManager::save() const
{
    return storage.saveToFile();
}

// Dang ky nguoi choi moi neu ten chua co trong danh sach
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

// Cap nhat thang/thua/hoa cho nguoi choi sau mot van
void PlayerManager::updateResult(const std::string &name, const std::string &result)
{
    storage.updateResult(name, result);
}

// Tim nguoi choi theo ten, tra ve nullptr neu khong co
PlayerData *PlayerManager::findPlayer(const std::string &name)
{
    return storage.searchPlayer(name);
}

// In danh sach tat ca nguoi choi va ty so W/L/D
void PlayerManager::printPlayers() const
{
    const auto &players = storage.getPlayers();
    if (players.empty())
    {
        std::cout << "Chua co du lieu nguoi choi.\n";
        return;
    }

    std::vector<PlayerData> rankedPlayers = players;
    std::sort(rankedPlayers.begin(), rankedPlayers.end(), [](const PlayerData &left, const PlayerData &right)
              {
                  if (left.score != right.score)
                  {
                      return left.score > right.score;
                  }
                  if (left.wins != right.wins)
                  {
                      return left.wins > right.wins;
                  }
                  if (left.losses != right.losses)
                  {
                      return left.losses < right.losses;
                  }
                  return left.name < right.name; });

    std::cout << "Bang xep hang nguoi choi:\n";
    for (size_t index = 0; index < rankedPlayers.size(); ++index)
    {
        const auto &player = rankedPlayers[index];
        int winRate = 0;
        if (player.gamesPlayed > 0)
        {
            winRate = (player.wins * 100) / player.gamesPlayed;
        }

        std::cout << index + 1 << ". " << player.name
                  << " | Score: " << player.score
                  << " | W/L/D: " << player.wins << "/" << player.losses << "/" << player.draws
                  << " | Win rate: " << winRate << "%"
                  << " | Da choi: " << player.gamesPlayed << " tran\n";
    }
}
