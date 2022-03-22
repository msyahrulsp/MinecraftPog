#include "inventory.hpp"

Inventory::Inventory() {
    this->slot = new Item*[SIZE];

    for (int i = 0; i < SIZE; i++) {
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
    for (int i = 0; i < SIZE; i++) {
        cout << this->slot[i]->getId() << ":" << this->slot[i]->getSide();
        if ((i + 1) % 9 != 0) {
            cout << "\t";
        } else {
            cout << endl;
        }
    }
}