#ifndef CRAFT_HPP
#define CRAFT_HPP

#include "item.hpp"

// STL
#include <string>
#include <map>

using namespace std;

class CraftingTableSlot {
    private:
        Item item;
        int quantity;
    public:
        CraftingTableSlot();

        // add item to slot
        void AddItemToCraftingTableSlotByItem(Item item, int qty);
        void AddItemToCraftingTableSlotByName(string itemName, int qty);

        // add and substract quantity of certain exist item from crafting table slot
        void AddItemQuantity(int qty);
        void DecreaseItemQuantity(int qty);
        
        // getters
        int getQuantity();
        Item getItem();
        
};

class CraftingTable {
    private:
        CraftingTableSlot TableSlot[3][3];
        map<int, vector<string>> recipes;
    public:
        // Create table of 9 x 9 matrix 
        CraftingTable();

        // Counting item on crafting table
        int CountItemOnTable();

        // 4. MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1> <CRAFTING_SLOT_ID_2> ...
        // MOVE I0 N C0 C1 C2 ... CN
        void PutItemToCraftingTableFromInventory(string craftingSlotId, int amount, string InventorySlotId);

        // check recipe
        bool EligibleForCrafting() const;

        // CRAFT -> di implementasi, panggil GIVE
        void Craft();
        // ngecek ada yg sesuai recipe ga
        
        // 6. MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>
        // MOVE I0 1 I1
        void PutItemToInventoryFromCraftingTable(string InventorySlotId, int amount, string craftingSlotId);
        
        // melihat table crafting
        void ShowCraftingTable();

        void ReadRecipe();
};

#endif
