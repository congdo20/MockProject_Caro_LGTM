#include "Game.h"
#include <iostream>
#include <limits>

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
        if (logic.isWinningMove(row, col))
        {
            logic.getBoard().display();
            std::cout << "Nguoi choi " << logic.getCurrentPlayer() << " chien thang!\n";
            break;
        }
        if (logic.isDraw())
        {
            logic.getBoard().display();
            std::cout << "Hoa! Ban co da day.\n";
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
        }
        else
        {
            std::cout << "Bot dang di...\n";
            auto [row, col] = bot.getNextMove(logic.getBoard());
            logic.makeMove(row, col);
            std::cout << "Bot chon: (" << row << ", " << col << ")\n";
        }

        if (logic.isWinningMove(logic.getHistory().back().row, logic.getHistory().back().col))
        {
            logic.getBoard().display();
            if (logic.getCurrentPlayer() == 'X')
            {
                std::cout << humanName << " chien thang!\n";
            }
            else
            {
                std::cout << "Bot chien thang!\n";
            }
            break;
        }
        if (logic.isDraw())
        {
            logic.getBoard().display();
            std::cout << "Hoa! Ban co da day.\n";
            break;
        }
        logic.switchPlayer();
    }
}
