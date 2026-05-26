#include "Menu.h"
#include <iostream>

int Menu::showMainMenu() const
{
    std::cout << "\n=== Game Caro 10x10 ===\n";
    std::cout << "1. Bat dau tran dau moi\n";
    std::cout << "2. Danh sach nguoi choi\n";
    std::cout << "3. Xem replay\n";
    std::cout << "0. Thoat\n";
    std::cout << "Lua chon: ";

    int choice;
    std::cin >> choice;
    return choice;
}

int Menu::showGameTypeMenu() const
{
    std::cout << "\n--- Lua chon kieu choi ---\n";
    std::cout << "1. 2 nguoi choi\n";
    std::cout << "2. Nguoi choi vs Bot\n";
    std::cout << "0. Quay lai\n";
    std::cout << "Lua chon: ";

    int choice;
    std::cin >> choice;
    return choice;
}
