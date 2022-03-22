#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include "item.hpp"
#include "tool.hpp"

#define SIZE 27
#define EMPTY ""

using namespace std;

// apa include item aja
class Inventory {
    private:
        // invent id?? di spek I0, I1, .., IN. cukup idx aja?
        Item **slot;
    public:
        Inventory();
        ~Inventory();

        Item* getSlot(int idx);

        // void setSlot(Item item);

        bool isEmpty(int idx);
        // ambil idx item di array
        // perlu handling item tool atau non tool
        // contoh: 48 item ke item yang punya 59
        // jadinya 64 43, 43 cari slot baru
        // int isExist(Item item);

        void display();
};

#endif