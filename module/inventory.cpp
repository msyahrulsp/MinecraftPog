#include "inventory.hpp"

Inventory::Inventory() {
    this->slot = new Item[SIZE];
}

Inventory::~Inventory() {
    delete[] this->slot;
}

Item Inventory::getSlot(int idx) {
    return this->slot[idx];
}

bool Inventory::isEmpty(int idx) {
    return this->slot[idx].getName() == EMPTY;
}

void display() {
    
}