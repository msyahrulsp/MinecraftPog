#ifndef _CRAFTING_HPP_
#define _CRAFTING_HPP_

#define SIZE 9
#define EMPTY NULL

#include "item.hpp"

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

        void displayCraftingTable() {
            cout << "CRAFTING TABLE | [IDXX QXX]\n";
            for (int i = 0; i < SIZE; i++) {
                if (this.slot[i] = EMPTY) {
                    cout << "[-- --]";
                }

                else {
                    int id = this.slot[i]->getId();
                    int quantity = this.slot[i]->getQuantity();
                    if (id < 10) {
                        cout << "[0" << id;
                    } else {
                        cout << "[" << id;
                    }

                    cout << " ";

                    if (quantity < 10) {
                        cout << "0" << quantity << "]";
                    } else {
                        cout << quantity << "]";
                    }
                }

                cout <<" ";

                if (i % 3 = 2) {
                    cout << '\n';
                }
            }
            cout << '\n';
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