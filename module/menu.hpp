#ifndef _MENU_HPP_
#define _MENU_HPP_
#pragma once

#include "item.hpp"
#include "tool.hpp"
#include "recipe.hpp"

#define SIZEI 27
#define SIZEC 9
#define AIR new NonTool("0", "-", "-", "-", 0)

using namespace std;

class Menu {
    protected:
        int size;
        Item **slot;
    public:
        Menu(int size);
        ~Menu();

        void addItem(Item* item);
        void discard(int idx, int qty);
        void use(int idx);
        void move(int src, int dest);
        void move(int src, int dest, Menu* destList);

        Item* getSlot(int idx);
        int findTool(string cat);

        bool isEmpty(int idx);
        int haveItem(string name);

        void display();
};

class Inventory : public Menu {
    public:
        Inventory();
};

class Crafting : public Menu {
    public:
        Crafting();

        int toolCount();
        int nonToolCount();

        bool validCombine();
        void erase();
        int getMinItem();
        void craft(ListRecipe* listRecipe, Inventory* invent, bool full, ListItem* listItem);
        Recipe* getCurCraft(bool mirror);
        bool checkRecipe(Recipe* recipe, bool mirror, ListItem* listItem);
};

#endif