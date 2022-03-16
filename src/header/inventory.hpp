#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"
#include <bits/stdc++.h>

using namespace std;

class Inventory {
    private:
        pair<Item, int> slot[3][9];
        int slotUsed;
    public:
        void showInventory();
        void addItemToInventory(string itemName, int itemQty);
        void discardItemfromInventory();
};

#endif
