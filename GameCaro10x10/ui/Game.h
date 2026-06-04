#ifndef GAME_H
#define GAME_H

#include "../core/Board.h"
#include "../core/GameLogic.h"
#include "../player/PlayerManager.h"
#include "../player/Player.h"
#include "../bot/Bot.h"
#include "../replay/Replay.h"

// Lop Game: dieu phoi van choi, cap nhat thong ke nguoi choi va luu/xem replay
class Game
{
private:
    PlayerManager playerManager;

public:
    Game();
    void playHumanVsHuman();                        // choi 2 nguoi tren cung may
    void playHumanVsBot();                          // nguoi (X) vs Bot (O)
    void showPlayers() const;                       // in danh sach nguoi choi da luu
    void searchPlayer() const;                      // tim va hien thi thong ke mot nguoi choi
    void showSavedReplays();                        // liet ke replay va cho phat lai
    void playReplayFromFile(const std::string &filename) const; // phat lai tu file
};

#endif
