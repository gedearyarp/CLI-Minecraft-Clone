#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"
#include <bits/stdc++.h>

using namespace std;

class Slot {
    private:
        Item item;
        int quantity;
    public:
        Slot();
        Slot(Item item, int qty);
        Slot(string item, int qty);

        void addItemSlot(int qty);
        void discardItemSlot(int qty);
        
        int getQuantity();
        Item getItem();

        bool isTool();
        bool isEmpty();
        bool isFull();
};

class Inventory {
    private:
        Slot slot[3][9];
        int slotUsed;
    public:
        Inventory();

        void showInventory();
        void give(string itemName, int itemQty);
        void discard(string slotId, int itemQty);
        void move(string srcSlot, int itemQty, vector<string> destSlot);

        void moveItoC(string srcSlot, vector<string> destSlot);
        void moveItoI(string srcSlot, string destSlot);
        void moveCtoI(string srcSlot, string destSlot);

        void exportFile();

        bool isFull();
};

#endif
