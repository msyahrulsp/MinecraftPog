#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "item.hpp"
#include "tool.hpp"

#define SIZEI 27
#define SIZEC 9
#define EMPTY ""

using namespace std;

class Inventory {
    private:
        Item **slot;
    public:
        Inventory();
        ~Inventory();

        Item* getSlot(int idx);

        // void setSlot(Item item);

        bool isEmpty(int idx);

        void display();
};

class Crafting {
    private:
        Item **slot;
    public:
        Crafting();
        ~Crafting();

        Item* getSlot(int idx);

        // void setSlot(Item item);

        bool isEmpty(int idx);

        void display();
};

#endif