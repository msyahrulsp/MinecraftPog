
#include <string>
#include <iostream>
#include "../module/crafting.hpp"
#include "../module/Item.hpp"
#include "../module/recipe.hpp"
Item NULL_ITEM = Item("-","-","-");
recipe::recipe(int r, int c) : row(r), col(c), hasil(NULL_ITEM), jumlah(0){
    this->bahan = new string[r*c];
    for (int i = 0; i < r*c; i++){
        this->bahan[i] = "-";
    }
};
recipe::recipe(int row, int col, Item i, int n) : row(row), col(col), hasil(i), jumlah(n)
{
    this->bahan = new string[row*col];
    for (int i = 0; i < row*col; i++){
        this->bahan[i] = "-";
    }
}

recipe::~recipe()
{
    delete[] this->bahan;
}
void recipe::setRecipe(int i, int j, string name){
    this->bahan[i*this->col + j] = name;
};

int recipe::checkCrafting(Crafting<Item> c){
    /*belom dicoba semoga udah bener */
    bool flag;
    int min = 0;
    for(int i = 0; i < 4 - this->row ; i++){
        for(int j = 0; j < 4 - this->col; i++){
            flag = true;
            for(int k = 0;  k < this->row; k++){
                for (int l = 0; l < this->col; l++){
                    if (c.getSlot(i * 3 + j).getName() != this->bahan[k*this->col + l]){
                        flag = false;
                        break;
                    } 
                }
                if (!flag) break;
            }
            if (flag) return flag;
        }
    }
    return flag;
}
void recipe::setItem(Item i){
    this->hasil = i;
};
Item recipe::getItem() const{
    return this->hasil;
};
void recipe::setJumlah(int n){
    this->jumlah = n;
}