// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "./src/header/move.hpp"
// #include "./src/implementation/readRecipe.cpp"

using namespace std;
int main()
{
    string configPath = "./config";
    string fileName = "item.txt";
    Inventory playerInventory = Inventory();
    CraftingTable playerCraftingTable = CraftingTable();
    // read item from config file
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);

    try{
        playerInventory.importFile();
    } catch (BaseException *err){
        (*err).printMessage();
    }

    // sample interaction
    string command;
    while (cin >> command)
    {
        try{
            if (command == "EXPORT")
            {
                string outputPath;
                cin >> outputPath;
                ofstream outputFile(outputPath);
                // TODO, fungsi exportfile harusnya nerima parameter path tempat export, terus ngelist semua item yang ada di inventory
            }
            else if (command == "CRAFT")
            {
                map<string, int> result = playerCraftingTable.craft();
                for (auto it = result.begin(); it != result.end(); ++it)
                {
                    playerInventory.give(it->first, it->second);
                }
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

                Move move = Move();
                cin >> slotSrc >> slotQty;
                getline(cin, slotDest);
                if (strstr(slotSrc.c_str(), I.c_str()) && strstr(slotDest.c_str(), I.c_str()))
                {
                    vector<string> slotDests;
                    slotDests.push_back(slotDest);
                    move.moveItoI(playerInventory, slotSrc, slotQty, slotDest);
                    // TODO move i to i, gangerti kenapa slotDest vector of string
                }
                else if (strstr(slotSrc.c_str(), C.c_str()) && strstr(slotDest.c_str(), I.c_str()))
                {
                    move.moveCtoI(playerInventory, slotSrc, slotQty, slotDest, playerCraftingTable);
                }
                else if (strstr(slotSrc.c_str(), I.c_str()) && strstr(slotDest.c_str(), C.c_str()))
                {
                    int spaces = 0;
                    vector<string> destVector;
                    for (int i = 0; i < slotDest.size(); i++)
                    {
                        if (slotDest[i] == ' ')
                        {
                            spaces++;
                        }
                        else
                        {
                            destVector[spaces] += slotDest[i];
                        }
                    }
                    for (int i = 0; i < destVector.size(); i++)
                    {
                        move.moveItoC(playerInventory, slotSrc, slotQty, destVector[i], playerCraftingTable);
                    }
                }
            }
            else if (command == "SHOW")
            {
                playerCraftingTable.showCraftingTable();
                cout << "Inventory: " << endl;
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
                string Slot;
                cin >> Slot;
                playerInventory.use(Slot);
            }
            else if (command == "EXIT")
            {
                break;
            }
            else
            {
                cout << "Invalid command" << endl;
            }
        } catch(BaseException *err){
            (*err).printMessage();
        }
        
    }
return 0;
}
