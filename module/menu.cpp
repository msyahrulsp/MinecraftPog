#include "menu.hpp"

Menu::Menu(int size) {
    this->size = size;
    this->slot = new Item*[size];

    for (int i = 0; i < size; i++) {
        this->slot[i] = new NonTool("0", "", "", "", 0);
    }
}

Menu::~Menu() {
    delete[] this->slot;
}

void giveItem(Item* item) {
    // search list item
    // copy item aja??   
}

Item* Menu::getSlot(int idx) {
    return this->slot[idx];
}

bool Menu::isEmpty(int idx) {
    return this->slot[idx]->getName() == EMPTY;
}

void Menu::display() {
    for (int i = 0; i < this->size; i++) {
        if (this->size == 9 && (i + 1) % (this->size / 3) == 1) cout << "\t\t\t";
        cout << this->slot[i]->getId() << ":" << this->slot[i]->getSide();
        if ((i + 1) % (this->size / 3) != 0) {
            cout << "\t";
        } else {
            cout << endl;
        }
    }
}

Inventory::Inventory() : Menu(SIZEI) {
    
}

Crafting::Crafting() : Menu(SIZEC) {
    
}