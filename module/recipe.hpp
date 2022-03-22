#include <string>
#include <iostream>
using namespace std;
class Recipe {
    private:
        int row;
        int col;
        string* items;
        string output;
        int nOutput;
    public:
        Recipe();
        Recipe(int row, int col);
        ~Recipe();

        int getNOutput();
        string getOutput();
        int getRow();
        int getCol();
        int getN();
        string getItems(int idx);
        void printItems();

        void setItems(int idx, string item);
        void setRowCol(int row, int col);
        void setMaterial(int idx, string name);
        void setOutput(string output, int nOutput);
};

class ListRecipe {
    private:
        int neff;
        int size;
        Recipe* recipes;
    public:
        ListRecipe();
        ~ListRecipe();

        void printInfo();

        void addRecipe(Recipe &recipe);

        friend void operator<<(ListRecipe& listRecipe, Recipe recipe);
};