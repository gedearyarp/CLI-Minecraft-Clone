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

using namespace std;
int main()
{
    string configPath = "./config";
    string fileName = "item.txt";
    Inventory playerInventory = Inventory();

    // read item from config file
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);

    // for (int i = 0; i < readItemConfig.getItemConfig().size(); i++){
    //   readItemConfig.getItemConfig()[i].itemInfo();
    //   cout << endl;
    // }

    // read recipes
    readItemConfig.displayItems();

    // TODO ADD READ RECIPE

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
            // TODO
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
            // need to handle multiple destinations
            cin >> slotSrc >> slotQty >> slotDest;
            // TODO
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