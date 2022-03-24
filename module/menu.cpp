#include "menu.hpp"

Menu::Menu(int size) {
    this->size = size;
    this->slot = new Item*[size];

    for (int i = 0; i < size; i++) {
        this->slot[i] = AIR;
    }
}

Menu::~Menu() {
    delete[] this->slot;
}

void Menu::addItem(Item* item) {
    if (item->getCategory() == "NONTOOL") {
        int idx = haveItem(item->getName());
        if (idx != -1) {
            if (this->slot[idx]->getSide() + item->getSide() <= 64) {
                this->slot[idx]->setSide(this->slot[idx]->getSide() + item->getSide());
                return;
            } else {
                item->setSide(item->getSide() - (64 - this->slot[idx]->getSide()));
                this->slot[idx]->setSide(64);
                this->addItem(item);
                return;
            }
        }
    }

    for (int i = 0; i < this->size; i++) {
        if (isEmpty(i)) {
            this->slot[i] = item;
            return;
        }
    }

    cout << "Slot penuh! ";

    if (item->getCategory() == "NONTOOL" && item->getSide() > 0) {
        cout << item->getSide() << " " << item->getName() << " jatuh ke tanah!" << endl;
    }

    if (item->getCategory() == "TOOL") {
        cout << item->getName() << " jatuh ke tanah!" << endl;
    }
}

void Menu::discard(int idx, int qty) {
    if (this->slot[idx]->getCategory() == "NONTOOL") {
        int n = this->slot[idx]->getSide();
        if (n >= qty) {
            this->slot[idx]->setSide(n - qty);
            if (this->slot[idx]->getSide() == 0) {
                this->slot[idx] = AIR;
            }
        } else {
            cout << "Item pada inventory kurang" << endl;
        }
    } else {
        if (qty > 1) {
            cout << "Item pada inventory kurang" << endl;
        } else {
            this->slot[idx] = AIR;
        }
    }
}

void Menu::use(int idx) {
    if (this->slot[idx]->getCategory() == "TOOL") {
        int n = this->slot[idx]->getSide();
        this->slot[idx]->setSide(n-1);
        if (n - 1 == 0) this->slot[idx] = AIR;
    } else {
        cout << "Command hanya untuk Tool" << endl;
    }
}

Item* Menu::getSlot(int idx) {
    return this->slot[idx];
}

int Menu::findTool() {
    for (int i = 0; i < this->size; i++) {
        if (this->slot[i]->getCategory() == "TOOL") {
            return i;
        }
    }
    return -1;
}

bool Menu::isEmpty(int idx) {
    return this->slot[idx]->getId() == "0";
}

int Menu::haveItem(string name) {
    for (int i = 0; i < this->size; i++) {
        int dn = this->slot[i]->getSide();
        string tName = this->slot[i]->getName();
        if (tName == name && dn < 64) return i;
    }
    return -1;
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

int Crafting::toolCount() {
    int idx = this->findTool();
    string name = this->slot[idx]->getName();
    if (idx != -1) {
        int res = 1;
        for (int i = idx+1; i < this->size; i++) {
            if (this->slot[i]->getName() == name) res++;
        }
        cout << "Here tc";
        return res;
    }
    return 0;
}

int Crafting::nonToolCount() {
    int count = 0;
    for (int i = 0; i < this->size; i++) {
        if (this->slot[i]->getCategory() == "NONTOOL"&& this->slot[i]->getId() != "0") count++;
    }
    cout << "Here ntc";
    return count;
}

bool Crafting::validCombine() {
    cout << "Here vc";
    int tc = this->toolCount();
    int ntc = this->nonToolCount();

    return (tc == 2 && ntc == 0);
}

void Crafting::erase() {
    for (int i = 0; i < this->size; i++) {
        if (this->slot[i]->getCategory() == "NONTOOL" && this->slot[i]->getId() != "0") {
            int n = this->slot[i]->getSide();
            this->slot[i]->setSide(n - 1);
            if (n - 1 == 0) this->slot[i] = AIR;
        } else {
            this->slot[i] = AIR;
        }
    }
}

void Crafting::craft(ListRecipe& listRecipe, Inventory* invent, bool full) {
    cout << "Here c";
    if (this->validCombine()) {
        string id, name;
        int dura = 0;
        for (int i = 0; i < this->size; i++) {
            if (this->slot[i]->getId() != "0") {
                id = this->slot[i]->getId();
                name = this->slot[i]->getName();
                dura += this->slot[i]->getSide();
            }
        }
        if (dura > 10) dura = 10;
        Item* tempItem = new Tool(id, name, "-", "TOOL", dura);
        invent->addItem(tempItem);
        this->erase();
        return;
    }
    cout << "HereA" << endl;
    for (int i = 0; i < listRecipe.getNeff(); i++) {
        Recipe* curRecipe = listRecipe.getRecipe(i);
        if (checkRecipe(curRecipe)) {
            invent->addItem(curRecipe->getOutput());
            this->erase();
            if (full) this->craft(listRecipe, invent, true);
            return;
        }
    }
}

bool Crafting::checkRecipe(Recipe* recipe) {
    cout << "Here1" << endl;
    int req = recipe->getRow() * recipe->getCol();
    for (int i = 0; i < 4 - recipe->getRow(); i++) {
        for (int j = 0; j < 4 - recipe->getCol(); j++) {
            bool equal = true;
            for (int k = i; k < recipe->getRow() && equal; k++) {
                for (int l = j; l < recipe->getCol() && equal; l++) {
                    string cName = this->slot[k + l]->getName();
                    string cType = this->slot[k + l]->getType();
                    string rec = recipe->getItems((k-i) + (j-l));
                    if (cName != rec && cType != rec) {
                        equal = false;
                    }
                }
            }
            if (equal) return true;
        }
    }

    // TODO Orientasi Tool
    cout << "Here" << endl;
    return false;
}