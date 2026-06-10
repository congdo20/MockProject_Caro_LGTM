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
#include <cstdlib>
#include <optional>
#include <vector>
// #define _Data_Players "data/players.txt"

// Khoi tao va nap danh sach nguoi choi tu file data/players.txt
Game::Game()
    : playerManager("data/players.txt") 
{
    playerManager.load();
}

// Xoa trang thai loi cua cin sau khi nhap sai
static void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Doc mot dong chua dung hai so nguyen (hang va cot)
static bool readPairOfInts(int &first, int &second)
{
    std::string line;
    if (!std::getline(std::cin >> std::ws, line) || line.empty()) // Doc dong va bo qua khoang trang dau vao
    {
        return false; // Tra ve false neu EOF hoac dong nhap rong
    }

    std::istringstream parser(line); // Phan tich dong nhap vao thanh hai so nguyen
    if (!(parser >> first >> second)) // Doc hai so nguyen, tra ve false neu khong hop le
    {
        return false;
    }

    std::string extra; // Kiem tra xem co du lieu nao sau hai so nguyen hay khong, neu co thi coi nhu nhap sai
    if (parser >> extra)
    {
        return false;
    }

    return true;
}

// Hoi nguoi choi nhap hang/cot, lap lai den khi hop le hoac EOF
static std::optional<std::pair<int, int>> askMove() // Tra ve cap (hang, cot) neu hop le, tra ve nullopt neu nguoi choi muon thoat (EOF)
{
    int row, col;
    while (true)
    {
        std::cout << "Nhap dong va cot: ";
        if (readPairOfInts(row, col))
        {
            return {{row, col}};
        }

        if (std::cin.eof()) // Neu nguoi choi nhap Ctrl+D (EOF) de thoat
        {
            std::cout << "\nKet thuc nhap. Thoat tran dau.\n";
            return std::nullopt;
        }

        std::cout << "Nhap khong hop le. Vui long nhap lai.\n";
    }
}

// Tao ten file replay kem timestamp, thay khoang trang bang '_'
static std::string makeReplayFilename(const std::string &baseName)
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
    localtime_s(&localTime, &time);

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

// Luu replay vao file va ghi duong dan vao data/replays.txt
static bool saveReplayFile(const Replay &replay)
{
    std::string filename = makeReplayFilename(replay.getName());
    if (!FileManager::saveReplay(replay, filename)) // Luu replay vao file, tra ve false neu that bai
    {
        return false;
    }

    std::ofstream indexFile("data/replays.txt", std::ios::app); // Mo file danh sach replay de ghi them ten file moi vao cuoi file
    if (indexFile.is_open())
    {
        indexFile << filename << '\n';
    }
    return true;
}

// Hoi nguoi dung co muon luu replay sau khi ket thuc van
static void promptSaveReplay(const Replay &replay)
{
    std::cout << "Ban co muon luu replay? (Y/N): ";
    std::string choiceLine;
    if (!std::getline(std::cin >> std::ws, choiceLine) || choiceLine.empty()) // Doc dong va bo qua khoang trang dau vao, tra ve neu EOF hoac dong nhap rong
    {
        return;
    }

    char choice = choiceLine[0];
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

// Van choi 2 nguoi: luu ten, ghi replay, cap nhat thang/thua/hoa
void Game::playHumanVsHuman()
{
    GameLogic logic;
    std::string nameX, nameO;
    std::cout << "Ten nguoi choi X: ";
    std::getline(std::cin >> std::ws, nameX);
    std::cout << "Ten nguoi choi O: ";
    std::getline(std::cin >> std::ws, nameO);

    playerManager.registerPlayer(nameX);
    playerManager.registerPlayer(nameO);
    playerManager.save();

    Replay replay(nameX + "_vs_" + nameO);

    while (true)
    {
        system("cls");
        logic.getBoard().display();
        std::cout << "Luot cua " << logic.getCurrentPlayer() << "\n";
        auto move = askMove();
        if (!move)
        {
            break;
        }
        auto [row, col] = *move;
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

// Van choi nguoi vs Bot: nguoi la X, Bot la O, chon cap do Bot
void Game::playHumanVsBot()
{
    GameLogic logic;
    std::string humanName;
    int level;
    std::cout << "Ten nguoi choi: ";
    std::getline(std::cin >> std::ws, humanName);

    std::string levelInput;
    while (true)
    {
        std::cout << "Chon do kho Bot (1-Easy, 2-Normal, 3-Hard): ";
        if (!std::getline(std::cin, levelInput)) // Doc dong, tra ve false neu EOF, thoat vong lap
        {
            clearInput();
            continue;
        }
        std::istringstream levelStream(levelInput);
        if (levelStream >> level && (level == 1 || level == 2 || level == 3)) // Neu doc duoc so va do kho hop le thi thoat vong lap
        {
            break;
        }
        std::cout << "Do kho khong hop le. Vui long nhap 1, 2 hoac 3.\n";
    }

    Bot bot(level, 'O');
    playerManager.registerPlayer(humanName);
    playerManager.save();

    Replay replay(humanName + "_vs_Bot");

    while (true)
    {
        system("cls");
        logic.getBoard().display();
        if (logic.getCurrentPlayer() == 'X')
        {
            std::cout << "Luot cua " << humanName << " (X)\n";
            auto move = askMove();
            if (!move)
            {
                break;
            }
            auto [row, col] = *move;
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

// In danh sach nguoi choi tu PlayerManager
void Game::showPlayers() const
{
    playerManager.printPlayers();
}

// Doc file replay va phat lai tung nuoc, nhan Enter de buoc tiep
void Game::playReplayFromFile(const std::string &filename) const
{
    Replay replay;
    if (!FileManager::loadReplay(replay, filename))
    {
        std::cout << "Khong the tai file replay: " << filename << "\n";
        return;
    }

    std::cout << "\n=== PHAT LAI: " << replay.getName() << " ===\n\n";

    Board board;
    board.reset();
    board.display();

    const auto &moves = replay.getMoves();
    for (size_t i = 0; i < moves.size(); ++i)
    {
        system("cls");
        std::cout << "Nuoc " << (i + 1) << "/" << moves.size();
        std::cout << " - " << moves[i].symbol << " tai (" << moves[i].row << ", " << moves[i].col << ")\n";

        board.makeMove(moves[i].row, moves[i].col, moves[i].symbol);
        board.display();

        std::cout << "Nhan Enter de tiep tuc..." << std::flush;
        std::string dummy;
        std::getline(std::cin, dummy);
    }

    std::cout << "Ket thuc replay.\n";
}

// Tim nguoi choi theo ten va hien thi thang/thua/hoa
void Game::searchPlayer() const
{
    std::cout << "Nhap ten nguoi choi can tim: ";
    std::string name;
    if (!std::getline(std::cin >> std::ws, name) || name.empty())
    {
        std::cout << "Ten khong hop le.\n";
        return;
    }

    PlayerData *player = const_cast<PlayerManager &>(playerManager).findPlayer(name);
    if (!player)
    {
        std::cout << "Khong tim thay nguoi choi \"" << name << "\".\n";
        return;
    }

    std::cout << "\n--- Thong tin nguoi choi ---\n";
    std::cout << "Ten  : " << player->name   << "\n";
    std::cout << "Thang: " << player->wins   << "\n";
    std::cout << "Thua : " << player->losses << "\n";
    std::cout << "Hoa  : " << player->draws  << "\n";
}

// Doc danh sach file replay tu data/replays.txt va cho nguoi dung chon phat lai
void Game::showSavedReplays()
{
    std::ifstream replayIndex("data/replays.txt");
    if (!replayIndex.is_open())
    {
        std::cout << "Khong tim thay file replay.\n";
        return;
    }

    std::vector<std::string> replayFiles;
    std::string replayFile;
    std::cout << "\nDanh sach replay da luu:\n";
    while (std::getline(replayIndex, replayFile))
    {
        if (replayFile.empty())
        {
            continue;
        }
        replayFiles.push_back(replayFile);
        std::cout << (replayFiles.size()) << ". " << replayFile << "\n";
    }

    if (replayFiles.empty())
    {
        std::cout << "Chua co replay nao duoc luu.\n";
        return;
    }

    std::cout << "0. Quay lai\n";
    std::cout << "Chon replay (0-" << replayFiles.size() << "): ";

    std::string choiceLine;
    if (!std::getline(std::cin, choiceLine))
    {
        return;
    }

    std::istringstream parser(choiceLine);
    int choice = -1;
    parser >> choice;

    if (choice > 0 && choice <= static_cast<int>(replayFiles.size()))
    {
        playReplayFromFile(replayFiles[choice - 1]);
    }
    else if (choice != 0)
    {
        std::cout << "Lua chon khong hop le.\n";
    }
}
