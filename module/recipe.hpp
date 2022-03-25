
#include <string>
#include <iostream>
#pragma once

#include "item.hpp"
#include "tool.hpp"

using namespace std;

class Recipe {
    private:
        int row;
        int col;
        string* items;
        Item* output;
    public:
        Recipe();
        Recipe(int row, int col);
        ~Recipe();

        int getNOutput();
        Item* getOutput();
        int getRow();
        int getCol();
        int getN();
        string getItems(int idx);
        void printItems();

        void setRowCol(int row, int col);
        void setMaterial(int idx, string name);
        void setOutput(Item* output);
};

class ListRecipe {
    private:
        int neff;
        int size;
        Recipe* recipes;
    public:
        ListRecipe();
        ~ListRecipe();

        Recipe* getRecipe(int idx);
        int getNeff();

        void printInfo();
        void addRecipe(Recipe &recipe);

        friend void operator<<(ListRecipe& listRecipe, Recipe recipe);
};