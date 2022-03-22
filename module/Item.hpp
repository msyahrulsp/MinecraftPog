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
        
        virtual int getSide() = 0;
        virtual void setSide(int num) = 0;
        // virtual void setDurability(int durability);
        // virtual int getQuantity() const;
        // virtual void setQuantity(int quantity);
};

class ListItem {
    private:
        Item** items;
        int size;
        int neff;
    public:
        ListItem();
        ~ListItem();

        void printInfo();

        string getId(int idx);
        string getName(int idx);
        string getType(int idx);
        string getCat(int idx);
        int findItem(string name);

        friend void operator<<(ListItem& listItem, Item &item);
};

#endif