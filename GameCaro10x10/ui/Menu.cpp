#include "Menu.h"
#include <iostream>
#include <sstream>

int Menu::showMainMenu() const
{
    std::cout << "\n=== Game Caro 10x10 ===\n";
    std::cout << "1. Bat dau tran dau moi\n";
    std::cout << "2. Danh sach nguoi choi\n";
    std::cout << "3. Xem replay\n";
    std::cout << "0. Thoat\n";
    std::cout << "Lua chon: ";

    std::string line;
    if (!std::getline(std::cin, line))
    {
        return -1;
    }

    std::istringstream parser(line);
    int choice = -1;
    parser >> choice;
    return choice;
}

int Menu::showGameTypeMenu() const
{
    std::cout << "\n--- Lua chon kieu choi ---\n";
    std::cout << "1. 2 nguoi choi\n";
    std::cout << "2. Nguoi choi vs Bot\n";
    std::cout << "0. Quay lai\n";
    std::cout << "Lua chon: ";

    std::string line;
    if (!std::getline(std::cin, line))
    {
        return -1;
    }

    std::istringstream parser(line);
    int choice = -1;
    parser >> choice;
    return choice;
}
