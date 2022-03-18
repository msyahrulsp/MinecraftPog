#include "Item.hpp"

int Item::numItems = 0;

Item::Item() : id(numItems) {
    this->name = "";
    this->type = "";
    this->category = "";
}

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

void Item::setName(string name) {
    this->name = name;
}

void Item::setType(string type) {
    this->type = type;
}

void Item::setCategory(string category) {
    this->category = category;
}

void Item::setId(int id) {
    this->id = id;
}

Tool::Tool() : Item("", "", "TOOL") {
    this->durability = 0;
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

Tool& Tool::operator=(const Tool& other) {
    this->name = other.name;
    this->type = other.type;
    this->category = other.category;
    this->id = other.id;
    this->numItems = other.numItems;
    this->durability = other.durability;
    return *this;
}

NonTool::NonTool() : Item("", "", "NONTOOL") {
    this->quantity = 0;
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

NonTool& NonTool::operator=(const NonTool& other) {
    this->name = other.name;
    this->type = other.type;
    this->category = other.category;
    this->id = other.id;
    this->numItems = other.numItems;
    this->quantity = other.quantity;
    return *this;
}