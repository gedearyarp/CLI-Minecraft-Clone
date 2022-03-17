#ifndef CRAFT_HPP
#define CRAFT_HPP

#include "item.hpp"
#include "Recipes.hpp"

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

        bool CraftingTable::isSameAsRecipe(SingleRecipe mirroredRecipe) const;

        // check recipe
        bool eligibleForCrafting() const;

        // CRAFT -> di implementasi, panggil GIVE
        void craft();
        // ngecek ada yg sesuai recipe ga
        
        // melihat table crafting
        void showCraftingTable();

        void readRecipes();
};

#endif
