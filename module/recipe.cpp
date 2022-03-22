
#include <string>
#include <iostream>
#include "recipe.hpp"

Recipe::Recipe() {
    this->row = 0;
    this->col = 0;
    this->items = new string[row*col];

    for (int i = 0; i < this->getN(); i++) {
        this->items[i] = "-";
}

    this->output = "-";
    this->nOutput = 0;
}

Recipe::Recipe(int row, int col) : row(row), col(col) {
    this->items = new string[row*col];

    for (int i = 0; i < this->getN(); i++) {
        this->items[i] = "-";
    }

    this->output = "-";
    this->nOutput = 0;
}

Recipe::~Recipe() {
    delete[] this->items;
}

string Recipe::getOutput() {
    return this->output;
}

void Recipe::printItems() {
    cout << "Output: " << this->output << ":" << this->nOutput << endl;
    for (int i = 0; i < this->getN(); i++) {
        cout << this->items[i];
        if ((i + 1) % this->col != 0) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
}

int Recipe::getNOutput() {
    return this->nOutput;
}

int Recipe::getRow() {
    return this->row;
}

int Recipe::getCol() {
    return this->col;
}

int Recipe::getN() {
    return this->row * this->col;
}

string Recipe::getItems(int idx) {
    return this->items[idx];
}

void Recipe::setItems(int idx, string item) {
    this->items[idx] = item;
}

void Recipe::setRowCol(int row, int col) {
    this->row = row;
    this->col = col;
}

void Recipe::setMaterial(int idx, string name){
    this->items[idx] = name;
};

void Recipe::setOutput(string output, int nOutput) {
    this->output = output;
    this->nOutput = nOutput;
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

ListRecipe::ListRecipe() {
    this->size = 100;
    this->neff = 1;
    this->recipes = new Recipe[this->size];
}

ListRecipe::~ListRecipe() {
    delete[] this->recipes;
}

void ListRecipe::printInfo() {
    // Kenapa 1?? i don't even know at this point
    // Kalau include 1 bakal output "-:0"
    for (int i = 1; i < this->neff; i++) {
        recipes[i].printItems();
        cout << endl;
    }
}

void ListRecipe::addRecipe(Recipe &recipe) {
    this->recipes[this->neff++] = recipe;
}

void operator<<(ListRecipe& listRecipe, Recipe recipe) {
    int idx = listRecipe.neff;
    listRecipe.recipes[idx].setRowCol(recipe.getRow(), recipe.getCol());
    
    for (int i = 0; i < recipe.getN(); i++) {
        listRecipe.recipes[idx].setItems(i, recipe.getItems(i));
    }

    listRecipe.recipes[idx].setOutput(recipe.getOutput(), recipe.getNOutput());
}