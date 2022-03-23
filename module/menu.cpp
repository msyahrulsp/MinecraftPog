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
    cout << "Inventory penuh!" << endl;
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

void Crafting::craft(ListRecipe* listRecipe) {
    for (int i = 0; i < listRecipe->getNeff(); i++) {
        Recipe* curRecipe = listRecipe->getRecipe(i);
        if (checkRecipe(curRecipe)) {
            this->addItem(curRecipe->getOutput());
            return;
        }
    }
    cout << "Tidak ada recipe yang sesuai" << endl;
}

bool Crafting::checkRecipe(Recipe* recipe) {
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