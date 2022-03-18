#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#define SIZE 27
#define EMPTY NULL

using namespace std;

// apa include item aja
template <class T>
class Inventory {
    private:
        // invent id?? di spek I0, I1, .., IN. cukup idx aja?
        T *slot[SIZE];
    public:
        Inventory() {
            this->slot = new T[SIZE];
            for (int i = 0; i < SIZE; i++) {
                this.slot[i] = EMPTY;
            }
        }

        T getSlot(int id) {
            return this.slot[i];
        }

        void setSlot(int id, T item) {
            this.slot[id] = T;
        }

        bool isEmpty(int id) {
            return this.slot[id] == EMPTY; 
        }

        // ambil idx item di array
        // perlu handling item tool atau non tool
        // contoh: 48 item ke item yang punya 59
        // jadinya 64 43, 43 cari slot baru
        int isExist(T item, bool aStack) {
            for (int i = 0; i < SIZE; i++) {
                if (this.slot[i] == item) {  // ?? 
                    return i;
                }
            }
            return -1;
        }

        void display() {
            for (int i; i < SIZE; i++) {
                cout << this.slot[i].name << "(" << this.slot[i].numItems << ")"
                cout << "\t";
                if ((i + 1) % 9 == 0) {
                    cout << endl;
                }
            }
        }

        // TODO > Pindah2 stack kudu di invent??
};

#endif