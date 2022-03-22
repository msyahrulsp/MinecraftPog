#include "item.hpp"

class Tool : public Item {
    private:
        int durability;
    public:
        Tool();
        Tool(string id, string name, string type, string category, int durability);
        Tool& operator=(const Tool&);
        
        int getSide() override;
        
        void setDurability(int durability);
};

class NonTool : public Item {
    private:
        int quantity;
    public:
        NonTool();
        NonTool(string id, string name, string type, string category, int quantity);
        NonTool& operator=(const NonTool&);
        
        int getSide() override;
        void setQuantity(int quantity);
};