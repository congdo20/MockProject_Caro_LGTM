#include "Game.h"
#include "../replay/FileManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <chrono>
#include <ctime>
#include <cctype>

Game::Game()
    : playerManager("data/players.txt")
{
    playerManager.load();
}

static void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static std::pair<int, int> askMove(const Board &board)
{
    int row, col;
    while (true)
    {
        std::cout << "Nhap dong va cot: ";
        if (std::cin >> row >> col)
        {
            break;
        }
        std::cout << "Nhap khong hop le. Vui long nhap lai.\n";
        clearInput();
    }
    return {row, col};
}

static std::string makeReplayFilename(const std::string &baseName)
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
    localtime_r(&time, &localTime);

    std::ostringstream filename;
    filename << "data/replay_" << baseName << "_" << std::put_time(&localTime, "%Y%m%d_%H%M%S") << ".txt";
    std::string result = filename.str();

    for (char &ch : result)
    {
        if (std::isspace(static_cast<unsigned char>(ch)))
        {
            ch = '_';
        }
    }
    return result;
}

static bool saveReplayFile(const Replay &replay)
{
    std::string filename = makeReplayFilename(replay.getName());
    if (!FileManager::saveReplay(replay, filename))
    {
        return false;
    }

    std::ofstream indexFile("data/replays.txt", std::ios::app);
    if (indexFile.is_open())
    {
        indexFile << filename << '\n';
    }
    return true;
}

static void promptSaveReplay(const Replay &replay)
{
    std::cout << "Ban co muon luu replay? (Y/N): ";
    char choice;
    std::cin >> choice;
    if (std::toupper(static_cast<unsigned char>(choice)) == 'Y')
    {
        if (saveReplayFile(replay))
        {
            std::cout << "Luu replay thanh cong.\n";
        }
        else
        {
            std::cout << "Luu replay that bai. Vui long kiem tra thu muc data.\n";
        }
    }
}

void Game::playHumanVsHuman()
{
    GameLogic logic;
    std::string nameX, nameO;
    std::cout << "Ten nguoi choi X: ";
    std::cin >> nameX;
    std::cout << "Ten nguoi choi O: ";
    std::cin >> nameO;

    playerManager.registerPlayer(nameX);
    playerManager.registerPlayer(nameO);
    playerManager.save();

    Replay replay(nameX + "_vs_" + nameO);

    while (true)
    {
        logic.getBoard().display();
        std::cout << "Luot cua " << logic.getCurrentPlayer() << "\n";
        auto [row, col] = askMove(logic.getBoard());
        if (!logic.makeMove(row, col))
        {
            std::cout << "Nuoc di khong hop le, thu lai.\n";
            continue;
        }

        replay.addMove(row, col, logic.getCurrentPlayer());

        if (logic.isWinningMove(row, col))
        {
            logic.getBoard().display();
            std::cout << "Nguoi choi " << logic.getCurrentPlayer() << " chien thang!\n";
            if (logic.getCurrentPlayer() == 'X')
            {
                playerManager.updateResult(nameX, "win");
                playerManager.updateResult(nameO, "lose");
            }
            else
            {
                playerManager.updateResult(nameO, "win");
                playerManager.updateResult(nameX, "lose");
            }
            playerManager.save();
            promptSaveReplay(replay);
            break;
        }
        if (logic.isDraw())
        {
            logic.getBoard().display();
            std::cout << "Hoa! Ban co da day.\n";
            playerManager.updateResult(nameX, "draw");
            playerManager.updateResult(nameO, "draw");
            playerManager.save();
            promptSaveReplay(replay);
            break;
        }
        logic.switchPlayer();
    }
}

void Game::playHumanVsBot()
{
    GameLogic logic;
    std::string humanName;
    int level;
    std::cout << "Ten nguoi choi: ";
    std::cin >> humanName;
    std::cout << "Chon do kho Bot (1-Easy, 2-Normal, 3-Hard): ";
    std::cin >> level;

    Bot bot(level, 'O');
    playerManager.registerPlayer(humanName);
    playerManager.save();

    Replay replay(humanName + "_vs_Bot");

    while (true)
    {
        logic.getBoard().display();
        if (logic.getCurrentPlayer() == 'X')
        {
            std::cout << "Luot cua " << humanName << " (X)\n";
            auto [row, col] = askMove(logic.getBoard());
            if (!logic.makeMove(row, col))
            {
                std::cout << "Nuoc di khong hop le, thu lai.\n";
                continue;
            }
            replay.addMove(row, col, 'X');
        }
        else
        {
            std::cout << "Bot dang di...\n";
            auto [row, col] = bot.getNextMove(logic.getBoard());
            logic.makeMove(row, col);
            replay.addMove(row, col, 'O');
            std::cout << "Bot chon: (" << row << ", " << col << ")\n";
        }

        if (logic.isWinningMove(logic.getHistory().back().row, logic.getHistory().back().col))
        {
            logic.getBoard().display();
            if (logic.getCurrentPlayer() == 'X')
            {
                std::cout << humanName << " chien thang!\n";
                playerManager.updateResult(humanName, "win");
            }
            else
            {
                std::cout << "Bot chien thang!\n";
                playerManager.updateResult(humanName, "lose");
            }
            playerManager.save();
            promptSaveReplay(replay);
            break;
        }
        if (logic.isDraw())
        {
            logic.getBoard().display();
            std::cout << "Hoa! Ban co da day.\n";
            playerManager.updateResult(humanName, "draw");
            playerManager.save();
            promptSaveReplay(replay);
            break;
        }
        logic.switchPlayer();
    }
}

void Game::showPlayers() const
{
    playerManager.printPlayers();
}

void Game::showSavedReplays() const
{
    std::ifstream replayIndex("data/replays.txt");
    if (!replayIndex.is_open())
    {
        std::cout << "Khong tim thay file replay.\n";
        return;
    }

    std::string replayFile;
    bool hasReplay = false;
    std::cout << "Danh sach replay da luu:\n";
    while (std::getline(replayIndex, replayFile))
    {
        if (replayFile.empty())
        {
            continue;
        }
        std::cout << "- " << replayFile << "\n";
        hasReplay = true;
    }

    if (!hasReplay)
    {
        std::cout << "Chua co replay nao duoc luu.\n";
    }
}
