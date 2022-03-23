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
    for (int i = 0; i < this->size; i++) {
        int dn = this->slot[i]->getSide();
        int dn2 = item->getSide();
        string name = this->slot[i]->getName();
        if (this->slot[i]->getCategory() == "NONTOOL") {
            // Ada item nontool yang bisa distack
            if (haveItem(item->getName())) {
                if (name == item->getName()) {
                    if (dn + dn2 <= 64) {
                        this->slot[i]->setSide(dn + dn2);
                        return;
                    } else {
                        this->slot[i]->setSide(64);
                        item->setSide(dn2 - (64 - dn));
                        // rekursif dari awal loop
                        this->addItem(item);
                    } 
                }
            } else {
                if (isEmpty(i)) {
                    this->slot[i] = item;
                    return;
                }
            }
        } else {
            if (isEmpty(i)) {
                this->slot[i] = item;
                return;
            }
        }
    }
    cout << "Inventory penuh! ";

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

bool Menu::haveItem(string name) {
    for (int i = 0; i < this->size; i++) {
        int dn = this->slot[i]->getSide();
        string tName = this->slot[i]->getName();
        if (tName == name && dn < 64) return true;
    }
    return false;
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
        return res;
    }
    return 0;
}

int Crafting::nonToolCount() {
    int count = 0;
    for (int i = 0; i < this->size; i++) {
        if (this->slot[i]->getCategory() == "NONTOOL") count++;
    }
    return count;
}

bool Crafting::validCombine() {
    int tc = this->toolCount();
    int ntc = this->nonToolCount();

    return (tc == 2 && ntc == 0);
}

void Crafting::erase() {
    for (int i = 0; i < this->size; i++) {
        if (this->slot[i]->getCategory() == "NONTOOL") {
            int n = this->slot[i]->getSide();
            this->slot[i]->setSide(n - 1);
            if (n - 1 == 0) this->slot[i] = AIR;
        } else {
            this->slot[i] = AIR;
        }
    }
}

void Crafting::craft(ListRecipe* listRecipe, Inventory* invent, bool full) {
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

    for (int i = 0; i < listRecipe->getNeff(); i++) {
        Recipe* curRecipe = listRecipe->getRecipe(i);
        if (checkRecipe(curRecipe)) {
            invent->addItem(curRecipe->getOutput());
            this->erase();
            if (full) this->craft(listRecipe, invent, true);
            return;
        }
    }
}

bool Crafting::checkRecipe(Recipe* recipe) {
    // Brute Force Pog
    for (int i = 0; i < this->size; i++) {
        // TODO
    }
}

// int Recipe::checkCrafting(Crafting<Item> c){
//     /*belom dicoba semoga udah bener */
//     bool flag;
//     int min = 0;
//     for(int i = 0; i < 4 - this->row ; i++){
//         for(int j = 0; j < 4 - this->col; i++){
//             flag = true;
//             for(int k = 0;  k < this->row; k++){
//                 for (int l = 0; l < this->col; l++){
//                     if (c.getSlot(i * 3 + j).getName() != this->items[k*this->col + l]){
//                         flag = false;
//                         break;
//                     } 
//                 }
//                 if (!flag) break;
//             }
//             if (flag) return flag;
//         }
//     }
//     return flag;
// }