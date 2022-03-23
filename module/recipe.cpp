
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

    this->output = new NonTool("0", "-", "-", "-", 0);
}

Recipe::Recipe(int row, int col) : row(row), col(col) {
    this->items = new string[row*col];

    for (int i = 0; i < this->getN(); i++) {
        this->items[i] = "-";
    }

    this->output = new NonTool("0", "-", "-", "-", 0);
}

Recipe::~Recipe() {
    delete[] this->items;
}

Item* Recipe::getOutput() {
    return this->output;
}

void Recipe::printItems() {
    cout << "Output: " << this->output->getName() << ":";
    cout << (this->output->getCategory() == "TOOL" ? 1 : this->output->getSide()) << endl;
    for (int i = 0; i < this->getN(); i++) {
        cout << this->items[i];
        if ((i + 1) % this->col != 0) {
            cout << " ";
        } else {
            cout << endl;
        }
    }
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

void Recipe::setOutput(Item* output) {
    this->output = output;
}

ListRecipe::ListRecipe() {
    this->size = 100;
    this->neff = 0;
    this->recipes = new Recipe[this->size];
}

ListRecipe::~ListRecipe() {
    delete[] this->recipes;
}

int ListRecipe::getNeff() {
    return this->neff;
}

Recipe* ListRecipe::getRecipe(int idx) {
    return &recipes[idx];
}

void ListRecipe::printInfo() {
    for (int i = 0; i < this->neff; i++) {
        recipes[i].printItems();
        cout << endl;
    }
}

void ListRecipe::addRecipe(Recipe &recipe) {
    this->recipes[this->neff++] = recipe;
}