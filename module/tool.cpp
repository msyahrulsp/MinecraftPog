#include "tool.hpp"

Tool::Tool() : Item("", "", "", "TOOL") {
    this->durability = 0;
}

Tool::Tool(string id, string name, string type, string category, int durability) : Item(id, name, type, "TOOL") {
    this->durability = durability;
}

int Tool::getSide() const {
    return this->durability;
}

void Tool::setDurability(int durability) {
    this->durability = durability;
}

Tool& Tool::operator=(const Tool& other) {
    this->id = other.id;
    this->name = other.name;
    this->type = other.type;
    this->category = other.category;
    this->id = other.id;
    this->durability = other.durability;
    return *this;
}

NonTool::NonTool() : Item("", "", "", "NONTOOL") {
    this->quantity = 0;
}

NonTool::NonTool(string id, string name, string type, string category, int quantity) : Item(id, name, type, "NONTOOL") {
    this->quantity = quantity;
}

int NonTool::getSide() const {
    return this->quantity;
}

void NonTool::setQuantity(int quantity) {
    this->quantity = quantity;
}

NonTool& NonTool::operator=(const NonTool& other) {
    this->id = other.id;
    this->name = other.name;
    this->type = other.type;
    this->category = other.category;
    this->id = other.id;
    this->quantity = other.quantity;
    return *this;
}