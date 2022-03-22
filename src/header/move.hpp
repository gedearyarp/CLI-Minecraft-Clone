#ifndef MOVE_HPP
#define MOVE_HPP

#include <bits/stdc++.h>
#include "craft.hpp"
#include "inventory.hpp"

using namespace std;
class Move {
    public:
        void moveItoI(Inventory inv, string srcSlot, int itemQty, string destSlot);
        void moveItoC(Inventory inv, string srcSlot, int itemQty, string destSlot, CraftingTable craft);
        void moveCtoI(Inventory inv, string srcSlot, int itemQty, string destSlot, CraftingTable craft);
};

#endif
