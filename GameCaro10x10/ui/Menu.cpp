#include "Menu.h"
#include <iostream>
#include <sstream>

// Hien thi menu chinh va doc lua chon tu nguoi dung
int Menu::showMainMenu() const
{
    std::cout << "\n=== Game Caro 10x10 ===\n";
    std::cout << "1. Bat dau tran dau moi\n";
    std::cout << "2. Danh sach nguoi choi\n";
    std::cout << "3. Xem replay\n";
    std::cout << "4. Tim kiem nguoi choi\n";
    std::cout << "0. Thoat\n";
    std::cout << "Lua chon: ";

    std::string line;
    if (!std::getline(std::cin >> std::ws, line))
    {
        return -1;
    }

    std::istringstream parser(line);
    int choice = -1;
    parser >> choice;
    return choice;
}

// Hien thi menu chon kieu choi (PvP hoac vs Bot)
int Menu::showGameTypeMenu() const
{
    std::cout << "\n--- Lua chon kieu choi ---\n";
    std::cout << "1. 2 nguoi choi\n";
    std::cout << "2. Nguoi choi vs Bot\n";
    std::cout << "0. Quay lai\n";
    std::cout << "Lua chon: ";

    std::string line;
    if (!std::getline(std::cin >> std::ws, line))
    {
        return -1;
    }

    std::istringstream parser(line);
    int choice = -1;
    parser >> choice;
    return choice;
}
