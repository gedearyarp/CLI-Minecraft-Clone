// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "inventory.hpp"
#include "item.hpp"
#include "itemconfig.hpp"
#include "recipes.hpp"
#include "craft.hpp"
#include "../implementation/readRecipe.cpp"

using namespace std;
int main()
{
    string configPath = "./config";
    string fileName = "item.txt";
    Inventory playerInventory = Inventory();
    CraftingTable playerCraftingTable = CraftingTable();
    
    // read item from config file
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);

    // for (int i = 0; i < readItemConfig.getItemConfig().size(); i++){
    //   readItemConfig.getItemConfig()[i].itemInfo();
    //   cout << endl;
    // }

    // read recipes
    Recipes newRecipes = ReadRecipesFromConfigToRecipesClass();
    vector<SingleRecipe> RecipesList = newRecipes.getRecipesList();
    for (int i = 0; i < newRecipes.getTotalRecipe(); i++)
    {
        SingleRecipe single = RecipesList[i];
        SingleRecipeVisualization(single);
    }
    map<int, vector<string>> newMapping = MapRecipesFromRecipesClass(newRecipes);


    // sample interaction
    string command;
    while (cin >> command)
    {
        if (command == "EXPORT")
        {
            string outputPath;
            cin >> outputPath;
            ofstream outputFile(outputPath);
            // TODO
        }
        else if (command == "CRAFT")
        {
            playerCraftingTable.craft(playerInventory);
        }
        else if (command == "GIVE")
        {
            string itemName;
            int itemQty;
            cin >> itemName >> itemQty;
            playerInventory.give(itemName, itemQty);
        }
        else if (command == "MOVE")
        {
            string slotSrc;
            int slotQty;
            string slotDest;
            string I = "I";
            string C = "C";
            // need to handle multiple destinations
            cin >> slotSrc >> slotQty >> slotDest;
            if (strstr(slotSrc.c_str(), I.c_str()) && strstr(slotDest.c_str(), I.c_str()))
            {
                //TODO
            }
            else if (strstr(slotSrc.c_str(), C.c_str()) && strstr(slotDest.c_str(), I.c_str()))
            {
                playerInventory.moveCtoI(slotSrc,slotQty,slotDest,playerCraftingTable);
            }
            else if (strstr(slotSrc.c_str(), I.c_str()) && strstr(slotDest.c_str(), C.c_str()))
            {
                playerInventory.moveItoC(slotSrc, slotQty, slotDest, playerCraftingTable);
            }

        }
        else if (command == "SHOW")
        {
            playerInventory.showInventory();
        }
        else if (command == "DISCARD")
        {
            string slotID;
            int itemQty;
            cin >> slotID >> itemQty;
            playerInventory.discard(slotID, itemQty);
        }
        else if (command == "USE")
        {
            int Slot;
            cin >> Slot;
            // TODO, inventory nyimpennya item, sementara use cuman punya class Tool
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
    return 0;
}