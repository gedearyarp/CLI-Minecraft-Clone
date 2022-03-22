#ifndef CRAFT_HPP
#define CRAFT_HPP

#include "itemConfig.hpp"
#include "recipes.hpp"

// STL
#include <string>
#include <map>

class CraftingTable {
    private:
        Item Table[3][3];
        Recipes recipes;
    public:
        // Create table of 9 x 9 matrix 
        CraftingTable();

        // Counting item on crafting table
        int countItemOnTable();

        void clearTable();

        Item getSlot(int slotKe) const;
        void setSlot(int slotKe, Item item);
        
        // melihat table crafting
        void showCraftingTable();

        // ngecek ada yg sesuai recipe ga
        bool itemInTableSameAsRecipePlacement(vector<vector<string>> recipePlacement);
        
        // CRAFT -> di implementasi, panggil GIVE
        map<string,int> craft();
};

#endif
