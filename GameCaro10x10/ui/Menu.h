#ifndef MENU_H
#define MENU_H

// Lop Menu: hien thi menu chinh va menu chon kieu choi
class Menu
{
public:
    int showMainMenu() const;     // tra ve lua chon menu chinh (hoac -1 neu loi nhap)
    int showGameTypeMenu() const; // tra ve kieu choi: 1-2 nguoi, 2-vs Bot, 0-quay lai
};

#endif
