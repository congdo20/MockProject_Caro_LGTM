#include "Storage.h"
#include <fstream>
#include <sstream>
#include <utility>
#include <cmath>

Storage::Storage(std::string file)
    : filename(std::move(file))
{
}

bool Storage::loadFromFile()
{
    players.clear();
    std::ifstream input(filename);
    if (!input.is_open())
    {
        return false;
    }

    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            continue;
        }
        std::istringstream parser(line);
        PlayerData data;
        parser >> data.name >> data.wins >> data.losses >> data.draws;
        if (!data.name.empty())
        {
            players.push_back(data);
        }
    }
    return true;
}

bool Storage::saveToFile() const
{
    std::ofstream output(filename);
    if (!output.is_open())
    {
        return false;
    }

    for (const auto &player : players)
    {
        output << player.name << ' ' << player.wins << ' ' << player.losses << ' ' << player.draws << '\n';
    }
    return true;
}

void Storage::updateResult(const std::string &name, const std::string &result)
{
    PlayerData *player = searchPlayer(name);
    if (!player)
    {
        PlayerData newPlayer;
        newPlayer.name = name;
        players.push_back(newPlayer);
        player = &players.back();
    }

    if (result == "win")
    {
        player->wins += 1;
    }
    else if (result == "lose")
    {
        player->losses += 1;
    }
    else if (result == "draw")
    {
        player->draws += 1;
    }
}

PlayerData *Storage::searchPlayer(const std::string &name)
{
    for (auto &player : players)
    {
        if (player.name == name)
        {
            return &player;
        }
    }
    return nullptr;
}

PlayerData *Storage::findMatchmaking(const std::string &name)
{
    if (players.empty())
    {
        return nullptr;
    }
    PlayerData *target = searchPlayer(name);
    if (!target)
    {
        return nullptr;
    }

    PlayerData *best = nullptr;
    for (auto &player : players)
    {
        if (player.name == name)
        {
            continue;
        }
        if (!best || std::abs(player.wins - target->wins) < std::abs(best->wins - target->wins))
        {
            best = &player;
        }
    }
    return best;
}

void Storage::addPlayer(const PlayerData &player)
{
    players.push_back(player);
}

const std::vector<PlayerData> &Storage::getPlayers() const
{
    return players;
}
