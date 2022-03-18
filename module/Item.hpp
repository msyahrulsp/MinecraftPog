#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
using namespace std;

class Item {
    protected:
        string name;
        string type;
        string category;
        const int id;
        static int numItems;
    public:
        Item(string name, string type, string category);
        int getId() const;
        string getName() const;
        string getType() const;
        string getCategory() const;
};

class Tool : public Item {
    private:
        int durability;
    public:
        Tool(string name, string type, string category, int durability);
        int getDurability() const;
        void setDurability(int durability);
};

class NonTool : public Item {
    private:
        int quantity;
    public:
        NonTool(string name, string type, string category, int quantity);
        int getQuantity() const;
        void setQuantity(int quantity);
};

#endif