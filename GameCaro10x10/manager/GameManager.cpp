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
            break;
        }
        case 2:
            std::cout << "Chuc nang hien thi danh sach nguoi choi dang duoc phat trien.\n";
            break;
        case 3:
            std::cout << "Chuc nang xem replay dang duoc phat trien.\n";
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
