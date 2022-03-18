
#include <string>
#include <iostream>
#include <crafting.hpp>
#include <Item.hpp>
#include <recipe.hpp>
recipe::recipe(int row, int col) : row(row), col(col)
{
    this->items = new string[row*col];
    for (int i = 0; i < row*col; i++){
        this->items[i] = "-";
    }
}

recipe::~recipe()
{
    delete[] this->items;
}
void recipe::setRecipe(int i, int j, string name){
    this->items[i*this->col + j] = name;
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
                    if (c.getSlot(i * 3 + j).getName() != this->items[k*this->col + l]){
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