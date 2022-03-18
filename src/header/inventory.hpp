#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <bits/stdc++.h>
#include "item.hpp"
#include "itemConfig.hpp"

using namespace std;

#define ROWSLOT 3
#define COLSLOT 9

class Inventory {
    private:
        Item slot[3][9];
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

        int countItem(string itemName) const;
        bool isFull() const;
};

#endif
