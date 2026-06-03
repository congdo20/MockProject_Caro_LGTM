#ifndef GAME_H
#define GAME_H

#include "../core/Board.h"
#include "../core/GameLogic.h"
#include "../player/PlayerManager.h"
#include "../player/Player.h"
#include "../bot/Bot.h"
#include "../replay/Replay.h"

class Game
{
private:
    PlayerManager playerManager;

public:
    Game();
    void playHumanVsHuman();
    void playHumanVsBot();
    void showPlayers() const;
    void showSavedReplays();
    void playReplayFromFile(const std::string &filename) const;
};

#endif
