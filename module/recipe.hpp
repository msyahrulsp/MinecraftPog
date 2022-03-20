
#include <string>
#include <iostream>
#include "../module/crafting.hpp"
#include "../module/Item.hpp"
using namespace std;
class recipe
{
private:
    int row,col;
    string* bahan;
    Item hasil;
    int jumlah;
public:
    recipe(int r, int c);
    recipe(int row, int col, Item i, int n);
    ~recipe();
    void setRecipe(int i, int j, string name);
    int checkCrafting(Crafting<Item> c);
    void setItem(Item i);
    Item getItem() const;
    void setJumlah(int n);
};
