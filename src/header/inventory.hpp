#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <bits/stdc++.h>
#include "itemConfig.hpp" 

using namespace std;

#define ROWSLOT 3
#define COLSLOT 9

#define MAXQTY 64
#define MAXINV 27

class Inventory {
    private:
        vector<vector<Item*>> slot;
        int slotUsed;
    public:
        Inventory();

        void showInventory();
        void give(string itemName, int itemQty);
        void discard(string slotId, int itemQty);
        void discardAll(string slotId);

        void importFile();
        void exportFile();

        Item locateSlot(int slotKe);
        Item *& slotItem(int slotKe);
        void setSlot(int slotKe, Item* item);
        int countItem(string itemName) const;
        bool isFull() const;

        
        void use(string srcSlot);
};

#endif
