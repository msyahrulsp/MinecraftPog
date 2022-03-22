#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "item.hpp"
#include "tool.hpp"

#define SIZEI 27
#define SIZEC 9
#define EMPTY ""

using namespace std;

class Menu {
    private:
        int size;
        Item **slot;
    public:
        Menu(int size);
        ~Menu();

        void giveItem(Item* item);

        Item* getSlot(int idx);

        bool isEmpty(int idx);

        void display();
};

class Inventory : public Menu {
    public:
        Inventory();
};

class Crafting : public Menu {
    public:
        Crafting();
};

#endif