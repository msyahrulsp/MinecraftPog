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

void Menu::move(int src, int dest) {
    Item* itemSrc = this->getSlot(src);
    Item* itemDest = this->getSlot(dest);

    if (itemSrc->getCategory() == "NONTOOL") {
        if (itemSrc->getName() == itemDest->getName()) {
            if (itemDest->getSide() <= 63) {
                itemSrc->setSide(itemSrc->getSide()-1);
                itemDest->setSide(itemDest->getSide()+1);

                if (itemSrc->getSide() == 0) {
                    this->slot[src] = AIR;
                }
            } else {
                cout << "Slot " << dest << " penuh" << endl;
            }
        } else if (itemDest->getId() == "0") {
            string id = itemSrc->getId();
            string name = itemSrc->getName();
            string type = itemSrc->getType();
            itemSrc->setSide(itemSrc->getSide()-1);

            if (itemSrc->getSide() == 0) {
                this->slot[src] = AIR;
            }

            this->slot[dest] = new NonTool(id, name, type, "NONTOOL", 1);
        } else {
            cout << "Item tidak sama" << endl;
        }
    } else {
        if (itemDest->getId() == "0") {
            this->slot[dest] = itemSrc;
            this->slot[src] = AIR;
        } else {
            cout << "Slot " << dest << " terisi" << endl;
        }
    }
}

void Menu::move(int src, int dest, Menu* destList) {
    Item* itemSrc = this->getSlot(src);
    Item* itemDest = destList->getSlot(dest);

    if (itemSrc->getCategory() == "NONTOOL") {
        if (itemSrc->getName() == itemDest->getName()) {
            if (itemDest->getSide() <= 63) {
                itemSrc->setSide(itemSrc->getSide()-1);
                itemDest->setSide(itemDest->getSide()+1);

                if (itemSrc->getSide() == 0) {
                    this->slot[src] = AIR;
                }
            } else {
                cout << "Slot " << dest << (destList->size == 9 ? "Crafting" : "Inventory");
                cout << " penuh" << endl;
            }
        } else if (itemDest->getId() == "0") {
            string id = itemSrc->getId();
            string name = itemSrc->getName();
            string type = itemSrc->getType();
            itemSrc->setSide(itemSrc->getSide()-1);

            if (itemSrc->getSide() == 0) {
                this->slot[src] = AIR;
            }

            destList->slot[dest] = new NonTool(id, name, type, "NONTOOL", 1);
        } else {
            cout << "Item tidak sama" << endl;
        }
    } else {
        if (itemDest->getId() == "0") {
            destList->slot[dest] = itemSrc;
            this->slot[src] = AIR;
        } else {
            cout << "Slot " << dest << (destList->size == 9 ? "Crafting" : "Inventory");
            cout << " terisi" << endl;
        }
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

int Menu::findTool(string cat) {
    for (int i = 0; i < this->size; i++) {
        bool airPass = (cat == "NONTOOL" ?  this->slot[i]->getId() != "0" : true);
        if (this->slot[i]->getCategory() == cat && airPass) {
            return i;
        }
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
    int idx = this->findTool("TOOL");
    if (idx != -1) {
        int res = 1;
        string name = this->slot[idx]->getName();
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
        if (this->slot[i]->getCategory() == "NONTOOL"&& this->slot[i]->getId() != "0") count++;
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
        if (this->slot[i]->getCategory() == "NONTOOL" && this->slot[i]->getId() != "0") {
            int n = this->slot[i]->getSide();
            this->slot[i]->setSide(n - 1);
            if (n - 1 == 0) this->slot[i] = AIR;
        } else {
            this->slot[i] = AIR;
        }
    }
}

int Crafting::getMinItem() {
    int idx = this->findTool("NONTOOL");
    int temp = this->slot[idx]->getSide();
    for (int i = 1; i < this->size; i++) {
        if (this->slot[i]->getSide() < temp && this->slot[i]->getId() != "0") temp = this->slot[i]->getSide();
    }
    return temp;
}

void Crafting::craft(ListRecipe* listRecipe, Inventory* invent, bool full, ListItem* listItem) {
    if (this->validCombine()) {
        // TODO handle kalau gk valid
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

        if (checkRecipe(curRecipe, true, listItem) || checkRecipe(curRecipe, false, listItem)) {
            int loop = (full ? this->getMinItem() : 1);
            string id = curRecipe->getOutput()->getId();
            string name = curRecipe->getOutput()->getName();
            string type = curRecipe->getOutput()->getType();
            string cat = curRecipe->getOutput()->getCategory();
            int qty = curRecipe->getOutput()->getSide();
            Item* tempItem;

            for (int i = 0; i < loop; i++) {
                if (cat == "TOOL") {
                    tempItem = new Tool(id, name, type, cat, 10);
                } else {
                    tempItem = new NonTool(id, name, type, cat, qty);
                }
                invent->addItem(tempItem);
                this->erase();
            }
            return;
        }
    }
}

Recipe* Crafting::getCurCraft() {
    // i j min i j max
    int* limit = new int[4];
    limit[0] = 10;
    limit[1] = 10;
    limit[2] = -1;
    limit[3] = -1;

    int temp;
    for (int i = 0; i < 9; i++) {
        if (this->slot[i]->getId() != "0") {
            int idx1 = i / 3;
            int idx2 = i % 3;
            if (limit[0] > idx1) limit[0] = idx1;
            if (limit[1] > idx2) limit[1] = idx2;
            if (limit[2] < idx1) limit[2] = idx1;
            if (limit[3] < idx2) limit[3] = idx2;
        }
    }

    int sizeI = limit[2] - limit[0] + 1;
    int sizeJ = limit[3] - limit[1] + 1;
    Recipe* res = new Recipe(sizeI, sizeJ);

    int idx = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i >= limit[0] && i <= limit[2] && j >= limit[1] && j <= limit[3]) {
                string name = this->slot[i * 3 + j]->getName();
                res->setMaterial(idx, name);
                idx++;
            }
        }
    }

    res->setOutput(AIR);

    return res;
}

bool Crafting::checkRecipe(Recipe* recipe, bool byBlock, ListItem* listItem) {
    Recipe* curMat = this->getCurCraft();
    string temp1, temp2;

    if (recipe->getRow() == curMat->getRow() && recipe->getCol() == curMat->getCol()) {
        for (int i = 0; i < curMat->getN(); i++) {
            if (byBlock) {
                temp1 = recipe->getItems(i);
                temp2 = curMat->getItems(i);
            } else {
                int idx = listItem->findItem(recipe->getItems(i), "type");
                if (idx != -1) {
                    temp1 = listItem->getType(idx);
                } else {
                    return false;
                }
                temp1 = listItem->getType(idx);
                if (idx != -1) {
                    temp1 = listItem->getType(idx);
                } else {
                    return false;
                }
                idx = listItem->findItem(curMat->getItems(i), "type");
                if (idx != -1) {
                    temp2 = listItem->getType(idx);
                } else {
                    return false;
                }
            }
            if (temp1 != temp2) return false;
        }
        return true;
    }
    return false;
}