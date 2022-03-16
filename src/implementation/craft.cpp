#include "../header/craft.hpp"
#include "readRecipe.cpp"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

CraftingTableSlot::CraftingTableSlot(){
    this->item = Item();
    this->quantity = 0;
}

void CraftingTableSlot::AddItemToCraftingTableSlotByItem(Item item, int qty){
    this->item = item;
    this->quantity = qty;
}

void CraftingTableSlot::AddItemToCraftingTableSlotByName(string itemName, int qty){
    this->item = Item(itemName);
    this->quantity = qty;
}

void CraftingTableSlot::AddItemQuantity(int qty){
    this->quantity = this->quantity + qty;
}

void CraftingTableSlot::DecreaseItemQuantity(int qty){
    this->quantity = this->quantity - qty;
}

Item CraftingTableSlot::getItem(){
    return this->item;
}

int CraftingTableSlot::getQuantity(){
    return this->quantity;
}

CraftingTable::CraftingTable()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->TableSlot[i][j] = CraftingTableSlot();
        }
    }
    this->recipes = ReadRecipes();
}

int CraftingTable::CountItemOnTable()
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->TableSlot[i][j].getQuantity() > 0)
            {
                count++;
            }
        }
    }
    return count;
}

bool CraftingTable::EligibleForCrafting() const
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

void CraftingTable::Craft()
{
    // TODO
}

void CraftingTable::ShowCraftingTable()
{
    cout << "Crafting Table" << endl;
    int idx = 0;
    for (int i = 0; i < 3; i++)
    {
        cout << "[ C", idx, ": ";
        for (int j = 0; j < 3; j++)
        {   
            string itemName = this->TableSlot[i][j].getItem().get_name();
            int itemQuantity = this->TableSlot[i][j].getQuantity();
            cout << itemName << " - " << itemQuantity << " ]";
            idx++;
            if (j != 3) { cout << " "; }
        }
        cout << endl;
    }
}
