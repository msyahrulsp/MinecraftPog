#ifndef _CRAFTING_HPP_
#define _CRAFTING_HPP_

#define SIZE 9
#define EMPTY NULL

using namespace std;

template <class T>
class Crafting {
    private:
        T *slot[SIZE];
    public:
        Crafting() {
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

        // TODO > Pindah2 stack kudu di invent??
};

#endif