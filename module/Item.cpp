#include "Item.hpp"

int Item::numItems = 0;

Item::Item(string name, string type, string category) : id(numItems+1) {
    this->name = name;
    this->type = type;
    this->category = category;
    numItems++;
}

int Item::getId() const {
    return this->id;
}

string Item::getName() const {
    return this->name;
}

string Item::getType() const {
    return this->type;
}

string Item::getCategory() const {
    return this->category;
}

Tool::Tool(string name, string type, string category, int durability) : Item(name, type, "TOOL") {
    this->durability = durability;
}

int Tool::getDurability() const {
    return this->durability;
}
void Tool::setDurability(int durability) {
    this->durability = durability;
}

NonTool::NonTool(string name, string type, string category, int quantity) : Item(name, type, "NONTOOL") {
    this->quantity = quantity;
}

int NonTool::getQuantity() const {
    return this->quantity;
}

void NonTool::setQuantity(int quantity) {
    this->quantity = quantity;
}