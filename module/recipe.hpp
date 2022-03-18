#include <string>
#include <iostream>
#include <crafting.hpp>
#include <Item.hpp>
using namespace std;
class recipe
{
private:
    int row,col;
    string* items;
public:
    recipe(int row, int col);
    ~recipe();
    void setRecipe(int i, int j, string name);
    int recipe::checkCrafting(Crafting<Item> c);
};
