#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "item.hpp"
#include <bits/stdc++.h>

using namespace std;

class Inventory {
    private:
        pair<item, int> [3][9];
    public:
        void showInventory();
        void addItemToInventory(string itemName, int itemQty);
        
};

#endif
