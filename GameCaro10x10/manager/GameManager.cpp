#include "GameManager.h"
#include "../ui/Menu.h"
#include "../ui/Game.h"
#include <iostream>

void GameManager::mainMenu()
{
    Menu menu;
    Game game;
    while (true)
    {
        int choice = menu.showMainMenu();
        if (choice == -1)
        {
            std::cout << "Thoat chuong trinh.\n";
            return;
        }
        switch (choice)
        {
        case 1:
        {
            int gameType = menu.showGameTypeMenu();
            if (gameType == 1)
            {
                game.playHumanVsHuman();
            }
            else if (gameType == 2)
            {
                game.playHumanVsBot();
            }
            else if (gameType == -1)
            {
                return;
            }
            break;
        }
        case 2:
            game.showPlayers();
            break;
        case 3:
            game.showSavedReplays();
            break;
        case 4:
            game.searchPlayer();
            break;
        case 0:
            std::cout << "Cam on ban da choi!\n";
            return;
        default:
            std::cout << "Lua chon khong hop le. Vui long chon lai.\n";
            break;
        }
    }
}
