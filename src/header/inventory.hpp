#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <bits/stdc++.h>
#include "item.hpp"
#include "itemConfig.hpp"
#include "../header/craft.hpp"

using namespace std;

#define ROWSLOT 3
#define COLSLOT 9

class Inventory
{
private:
    Item slot[3][9];
    int slotUsed;

public:
    Inventory();

    void showInventory();
    void give(string itemName, int itemQty);
    void discard(string slotId, int itemQty);
    void discardAll(string slotId);
    void move(string srcSlot, int itemQty, vector<string> destSlot);

    Item locateSlot(int slotKe);
    void setSlot(int slotKe, Item item);

    void moveItoC(string srcSlot, int itemQty, string destSlot, CraftingTable craft);
    void moveItoI(string srcSlot, int itemQty, string destSlot);
    void moveCtoI(string srcSlot, int itemQty, string destSlot);

    void exportFile();
    int countItem(string itemName) const;
    bool isFull() const;
};

#endif
