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

    // UNCOMMENT INI KALO MAU INVENTORYNYA UDAH ADA ISINYA
    // try
    // {
    //     playerInventory.importFile();
    // }
    // catch (BaseException *err)
    // {
    //     (*err).printMessage();
    // }

    cout << "__________.__     __        __    _________                          " << endl;
    cout << "\\______   \\__|   |__|____ _/  |_  \\_   ___ \\     .__         .__     " << endl;
    cout << " |     ___/  |   |  \\__  \\\\   __\\ /    \\  \\/   __|  |___   __|  |___ " << endl;
    cout << " |    |   |  |   |  |/ __ \\|  |   \\     \\____ /__    __/  /__    __/ " << endl;
    cout << " |____|   |__/\\__|  (____  /__|    \\______  /    |__|        |__|    " << endl;
    cout << "             \\______|    \\/               \\/  MINECRAFT CLONE V.01" << endl;
    cout << endl << "Enter \'HELP\' to show all valid command." << endl;


    // sample interaction
    string command;
    cout << "\nINPUT COMMAND: ";
    while (cin >> command)
    {
        try
        {
            if (command == "EXPORT")
            {
                string fileName;
                cin >> fileName;
                playerInventory.exportFile(fileName);
                cout << "EXPORT SUCCESS" << '\n';
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
                cout << "GIVE SUCCESS" << '\n';
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
                cout << "MOVE SUCCESS" << '\n';
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
                cout << "DISCARD SUCCESS" << '\n';
            }
            else if (command == "USE")
            {
                string Slot;
                cin >> Slot;
                playerInventory.use(Slot);
                cout << "USE SUCCESS" << '\n';
            }
            else if (command == "EXIT")
            {
                cout << "GOODBYE!" << '\n';
                break;
            }
            else if (command == "HELP")
            {
                cout << "1. SHOW" << '\n';
                cout << "2. GIVE <ITEM_NAME> <ITEM_QTY>" << '\n';
                cout << "3. DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY>" << '\n';
                cout << "4. MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1>" << '\n';
                cout << "5. MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST>" << '\n';
                cout << "6. MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>" << '\n';
                cout << "7. USE <INVENTORY_SLOT_ID>" << '\n';
                cout << "8. CRAFT" << '\n';
                cout << "9. EXPORT <NAMA_FILE>" << '\n';
            }
            else
            {
                cout << "Command is invalid. Enter 'HELP' for more." << endl;
            }
        }
        catch (BaseException *err)
        {
            (*err).printMessage();
        }
        cout << "\nINPUT COMMAND: ";
    }
    return 0;
}
