// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "./src/header/move.hpp"

using namespace std;
int main()
{
    string configPath = "./config";
    string fileName = "item.txt";
    Inventory playerInventory = Inventory();
    CraftingTable playerCraftingTable = CraftingTable();
    // read item from config file
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);

    try
    {
        playerInventory.importFile();
    }
    catch (BaseException *err)
    {
        (*err).printMessage();
    }

    // sample interaction
    string command;
    while (cin >> command)
    {
        try
        {
            if (command == "EXPORT")
            {
                string fileName;
                cin >> fileName;
                playerInventory.exportFile(fileName);
            }
            else if (command == "CRAFT")
            {
                map<string, int> result = playerCraftingTable.craft();
                for (auto it = result.begin(); it != result.end(); ++it)
                {
                    
                    string itemName = it->first;
                    stringstream ss(itemName);
                    string word;
                    ss >> word;

                    if (word == "ADD_DURABILITY") {
                        ss >> word;
                        playerInventory.giveToolWithDurability(word, 1, it->second);
                    } else {
                        playerInventory.give(it->first,it->second);
                    }
                }
            }
            else if (command == "GIVE")
            {
                string itemName;
                int itemQty;
                cin >> itemName >> itemQty;
                if(cin.fail())
                {
                    throw new CustomException("Invalid Input");
                }
                playerInventory.give(itemName, itemQty);
            }
            else if (command == "MOVE")
            {
                string slotSrc;
                int slotQty;
                string slotDest;

                int i;
                string I = "I";
                string C = "C";

                Move move = Move();
                cin >> slotSrc >> slotQty;
                getline(cin, slotDest);
                slotDest.erase(remove(slotDest.begin(), slotDest.end(), ' '), slotDest.end());
                
                if (cin.fail())
                {
                    throw new CustomException("Invalid Input");
                }

                if (strstr(slotSrc.c_str(), I.c_str()) && strstr(slotDest.c_str(), I.c_str()))
                {
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
                    
                    for (int i = 0; i < slotDest.size(); i += 2)
                    {
                        string added = string(1,slotDest[i]) + string(1,slotDest[i+1]);
                        destVector.push_back(added);
                    }

                    if (destVector.size() != slotQty)
                    {
                        throw new CustomException("Too many slot destination");
                    }

                    for (int i = 0; i < slotQty; i++)
                    {
                        move.moveItoC(playerInventory, slotSrc, slotQty, destVector.at(i), playerCraftingTable);
                    }
                }
            }
            else if (command == "SHOW")
            {
                playerCraftingTable.showCraftingTable();
                playerInventory.showInventory();
            }
            else if (command == "DISCARD")
            {
                string slotID;
                int itemQty;
                cin >> slotID >> itemQty;
                if (cin.fail())
                {
                    throw new CustomException("Invalid Input");
                }
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
        }
        catch (BaseException *err)
        {
            (*err).printMessage();
        }
    }
    return 0;
}
