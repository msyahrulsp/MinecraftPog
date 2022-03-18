#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>
using namespace std;

class Item {
    protected:
        string name;
        string type;
        string category;
        int id;
        static int numItems;
    public:
        Item();
        Item(string name, string type, string category);
        int getId() const;
        string getName() const;
        string getType() const;
        string getCategory() const;
        void setName(string name);
        void setType(string type);
        void setCategory(string category);
        void setId(int id);
        virtual int getDurability() const;
        virtual void setDurability(int durability);
        virtual int getQuantity() const;
        virtual void setQuantity(int quantity);
};

class Tool : public Item {
    private:
        int durability;
    public:
        Tool();
        Tool(string name, string type, string category, int durability);
        int getDurability() const;
        void setDurability(int durability);
        Tool& operator=(const Tool&);
};

class NonTool : public Item {
    private:
        int quantity;
    public:
        NonTool();
        NonTool(string name, string type, string category, int quantity);
        int getQuantity() const;
        void setQuantity(int quantity);
        NonTool& operator=(const NonTool&);
};

#endif