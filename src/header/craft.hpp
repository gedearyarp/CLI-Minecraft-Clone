#ifndef CRAFT_HPP
#define CRAFT_HPP

// STL
#include <string>

using namespace std;

template<class T>
class CraftingTable {
    private:
        T* Table;
    public:
        // Create table of 9 x 9 matrix 
        CraftingTable();

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
        
        void showTable();

};

#endif
