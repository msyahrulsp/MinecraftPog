#include "item.hpp"

class Tool : public Item {
    private:
        int durability;
    public:
        Tool();
        Tool(string id, string name, string type, string category, int durability);
        int getDurability() const;
        void setDurability(int durability);
        int getQuantity() const;
        Tool& operator=(const Tool&);
};

class NonTool : public Item {
    private:
        int quantity;
    public:
        NonTool();
        NonTool(string id, string name, string type, string category, int quantity);
        int getQuantity() const;
        void setQuantity(int quantity);
        NonTool& operator=(const NonTool&);
};