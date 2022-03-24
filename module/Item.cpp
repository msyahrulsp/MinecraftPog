#include "item.hpp"

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

Item::Item(const Item& item) {
    this->id = item.id;
    this->name = item.name;
    this->type = item.type;
    this->category = item.category;
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

ListItem::ListItem() {
    this->size = 100;
    this->neff = 0;
    this->items = new Item*[this->size];
}

ListItem::~ListItem() {
    delete[] this->items;
}

void ListItem::printInfo() {
    for (int i = 0; i < this->neff; i++) {
        cout << "Tool ke " << i+1 << endl;
        cout << this->items[i]->getId() << " ";
        cout << this->items[i]->getName() << " ";
        cout << this->items[i]->getType() << " ";
        cout << this->items[i]->getCategory();
        cout << endl;
    }
}

string ListItem::getId(int idx) {
    return this->items[idx]->getId();
}

string ListItem::getName(int idx) {
    return this->items[idx]->getName();
}

string ListItem::getType(int idx) {
    return this->items[idx]->getType();
}

string ListItem::getCat(int idx) {
    return this->items[idx]->getCategory();
}

int ListItem::findItem(string name, string type) {
    if (type == "nama") {
        for (int i = 0; i < this->neff; i++) {
            if (this->items[i]->getName() == name) return i;
        }
    } else {
        for (int i = 0; i < this->neff; i++) {
            if (this->items[i]->getType() == name) return i;
        }
    }
    return -1;
}

void operator<<(ListItem& listItem, Item &item) {
    listItem.items[listItem.neff++] = &item;
}