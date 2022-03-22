#include "Item.hpp"

Item::Item() {
    this->id = "";
    this->name = "";
    this->type = "";
    this->category = "";
}

Item::Item(string id, string name, string type, string category) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->category = category;
}

string Item::getId() const {
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

// Tool::Tool() : Item("", "", "TOOL") {
//     this->durability = 0;
// }

// Tool::Tool(string name, string type, string category, int durability, int quantity) : Item(name, type, "TOOL") {
//     this->durability = durability;
//     this->quantity = quantity;
// }

// int Tool::getDurability() const {
//     return this->durability;
// }

// void Tool::setDurability(int durability) {
//     this->durability = durability;
// }

// int Tool::getQuantity() const {
//     return this->quantity;
// }

// Tool& Tool::operator=(const Tool& other) {
//     this->id = other.id;
//     this->name = other.name;
//     this->type = other.type;
//     this->category = other.category;
//     this->id = other.id;
//     this->numItems = other.numItems;
//     this->durability = other.durability;
//     return *this;
// }

// NonTool::NonTool() : Item("", "", "NONTOOL") {
//     this->quantity = 0;
// }

// NonTool::NonTool(string name, string type, string category, int quantity) : Item(name, type, "NONTOOL") {
//     this->quantity = quantity;
// }

// int NonTool::getQuantity() const {
//     return this->quantity;
// }

// void NonTool::setQuantity(int quantity) {
//     this->quantity = quantity;
// }

// NonTool& NonTool::operator=(const NonTool& other) {
//     this->id = other.id;
//     this->name = other.name;
//     this->type = other.type;
//     this->category = other.category;
//     this->id = other.id;
//     this->numItems = other.numItems;
//     this->quantity = other.quantity;
//     return *this;
// }

ListItem::ListItem() {
    this->size = 100;
    this->neff = 0;
    this->items = new Item[this->size];
}

ListItem::~ListItem() {
    delete[] this->items;
}

void ListItem::printInfo() {
    for (int i = 0; i < this->neff; i++) {
        cout << "Tool ke " << i+1 << endl;
        cout << this->items[i].getId() << " ";
        cout << this->items[i].getName() << " ";
        cout << this->items[i].getType() << " ";
        cout << this->items[i].getCategory();
        cout << endl;
    }
}

void operator<<(ListItem& listItem, Item item) {
    listItem.items[listItem.neff++] = item;
}