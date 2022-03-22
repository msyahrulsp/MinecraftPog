#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
#include <iostream>
using namespace std;

class Item {
    protected:
        string id;
        string name;
        string type;
        string category;
    public:
        Item();
        Item(string id, string name, string type, string category);
        string getId() const;
        string getName() const;
        string getType() const;
        string getCategory() const;
        void setName(string name);
        void setType(string type);
        void setCategory(string category);
        void setId(int id);
        // virtual int getDurability() const;
        // virtual void setDurability(int durability);
        // virtual int getQuantity() const;
        // virtual void setQuantity(int quantity);
};

// class Tool : public Item {
//     private:
//         int durability;
//     public:
//         Tool();
//         Tool(string name, string type, string category, int durability, int quantity);
//         int getDurability() const;
//         void setDurability(int durability);
//         int getQuantity() const;
//         Tool& operator=(const Tool&);
// };

// class NonTool : public Item {
//     private:
//         int quantity;
//     public:
//         NonTool();
//         NonTool(string name, string type, string category, int quantity);
//         int getQuantity() const;
//         void setQuantity(int quantity);
//         NonTool& operator=(const NonTool&);
// };

class ListItem {
    private:
        Item* items;
        int size;
        int neff;
    public:
        ListItem();
        ~ListItem();

        void printInfo();

        friend void operator<<(ListItem& listItem, Item item);
};

#endif