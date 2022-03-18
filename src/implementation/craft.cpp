#include "../header/craft.hpp"
#include "readRecipe.cpp"

using namespace std;

CraftingTable::CraftingTable()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->Table[i][j] = Item();
        }
    }
};

int CraftingTable::countItemOnTable()
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->Table[i][j].getName() != "-")
            {
                count++;
            }
        }
    }
    return count;
}

bool CraftingTable::isSameAsRecipe(SingleRecipe mirroredRecipe)
{
    // TODO
    // for (int i=0; i<3; i++) {
    //     for (int j=0; j<3; j++) {
    //         // t
    //         if (this->Table[i][j].getName() != mirroredRecipe.getItemPlacement()[i][j]) {
    //             return false;
    //         }
    //     }
    // }
    // return true;
}

bool CraftingTable::eligibleForCrafting() const
{
    // TODO
    // int itemInTable = countItemOnTable();
    // bool canBeingCrafted = false;
    // // BIRCH_PLANK = 1
    // // DIAMOND_AXE = 5
    // // DIAMOND_PICKAXE = 5
    // // DIAMOND_SWORD = 3
    // // IRON_AXE = 5
    // // IRON_INGOT = 9
    // // IRON_NUGGET = 1
    // // IRON_PICKAXE = 5
    // // IRON_SWORD = 3
    // // OAK_PLANK = 1
    // // SPRUCE_PLANK = 1
    // // STICK = 2
    // // STONE_AXE = 5
    // // STONE_PICKAXE = 5
    // // STONE_SWORD  = 3
    // // WOODEN_AXE = 5
    // // WOODEN_PICKAXE = 5
    // // WOODEN_SWORD = 3
    // // 1 : BIRCH_PLANK, IRON_NUGGET, OAK_PLANK, SPRUCE_PLANK
    // // 2 : STICK
    // // 3 : DIAMOND_SWORD, IRON_SWORD, STONE_SWORD, WOODEN_SWORD
    // // 5 : DIAMOND_AXE, DIAMOND_PICKAXE, IRON_AXE, IRON_PICKAXE, STONE_AXE, STONE_PICKAXE
    // // 9 : IRON INGOT
    // if (itemInTable==1){
    //     // BIRCH_PLANK
    //     // IRON_NUGGET
    //     // OAK_PLANK
    //     // SPRUCE_PLANK
    // }if (itemInTable==2){
    //     // STICK
    // }if (itemInTable==3){
    //     // DIAMOND_SWORD
    //     // IRON_SWORD
    //     // STONE_SWORD
    //     // WOODEN_SWORD
    // }if (itemInTable==5){
    //     // DIAMOND_AXE
    //     // DIAMOND_PICKAXE
    //     // IRON_AXE
    //     // IRON_PICKAXE
    //     // STONE_AXE
    //     // STONE_PICKAXE
    // }
    // if (itemInTable==9){
    //     // IRON INGOT
    // }
}

Item CraftingTable::getSlot(int slotKe) const
{
    return this->Table[slotKe / 3][slotKe % 3];
}

void CraftingTable::setSlot(int slotKe, Item item)
{
    this->Table[slotKe / 3][slotKe % 3] = item;
}

void CraftingTable::craft()
{
    // TODO
}

void CraftingTable::showCraftingTable()
{
    cout << "Crafting Table" << endl;
    int idx = 0;
    for (int i = 0; i < 3; i++)
    {
        cout << "[ C", idx, ": ";
        for (int j = 0; j < 3; j++)
        {
            string name = Table[i][j].getName();
            int quantity = Table[i][j].getQuantity();
            cout << name << " - " << quantity << " ]";
            if (j != 2)
            {
                cout << " ";
            }
            idx++;
        }
        cout << endl;
    }
}

void CraftingTable::readRecipes()
{
    this->recipes = ReadRecipesFromConfigToRecipesClass();
}
