#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <bits/stdc++.h>
#include "item.hpp"
#include "itemConfig.hpp"
#include "craft.hpp"

using namespace std;

#define ROWSLOT 3
#define COLSLOT 9

#define MAXQTY 64

class Inventory {
    private:
        Item slot[ROWSLOT][COLSLOT];
        int slotUsed;
    public:
        Inventory();

        void showInventory();
        void give(string itemName, int itemQty);
        void discard(string slotId, int itemQty);
        void discardAll(string slotId);

        void moveItoI(string srcSlot, int itemQty, vector<string> destSlot);
        void moveItoC(string srcSlot, int itemQty, string destSlot, CraftingTable craft);
        void moveCtoI(string srcSlot, int itemQty, string destSlot, CraftingTable craft);
        
        void exportFile();

        Item locateSlot(int slotKe);
        void setSlot(int slotKe, Item item);
        int countItem(string itemName) const;
        bool isFull() const;

};

#endif
