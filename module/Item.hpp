#include <string>
using namespace std;

class Item {
    protected:
        string nama;
        string jenis;
        string variasi;
    public:
        Item(string nama, string jenis, string variasi);
};

class Tool : public Item {
    private:
        int durability;
    public:
        Tool();
        void useDurability();
};

class NonTool : public Item {

};