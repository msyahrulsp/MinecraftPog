#include "menu.hpp"

Inventory::Inventory() {
    this->slot = new Item*[SIZEI];

    for (int i = 0; i < SIZEI; i++) {
        this->slot[i] = new NonTool("0", "", "", "", 0);
    }
}

Inventory::~Inventory() {
    delete[] this->slot;
}

Item* Inventory::getSlot(int idx) {
    return this->slot[idx];
}

bool Inventory::isEmpty(int idx) {
    return this->slot[idx]->getName() == EMPTY;
}

void Inventory::display() {
    for (int i = 0; i < SIZEI; i++) {
        cout << this->slot[i]->getId() << ":" << this->slot[i]->getSide();
        if ((i + 1) % 9 != 0) {
            cout << "\t";
        } else {
            cout << endl;
        }
    }
}

Crafting::Crafting() {
    this->slot = new Item*[SIZEC];

    for (int i = 0; i < SIZEC; i++) {
        this->slot[i] = new NonTool("0", "", "", "", 0);
    }
}

Crafting::~Crafting() {
    delete[] this->slot;
}

Item* Crafting::getSlot(int idx) {
    return this->slot[idx];
}

bool Crafting::isEmpty(int idx) {
    return this->slot[idx]->getName() == EMPTY;
}

void Crafting::display() {
    for (int i = 0; i < SIZEC; i++) {
        if ((i + 1) % 3 == 1) cout << "\t\t\t";
        cout << this->slot[i]->getId() << ":" << this->slot[i]->getSide();
        if ((i + 1) % 3 != 0) {
            cout << "\t";
        } else {
            cout << endl;
        }
    }
}