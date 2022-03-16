#include <iostream>
#include "../header/inventory.hpp"

using namespace std;

Inventory::Inventory()
{
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 9; j++){
            this->slot[i][j] = Item();
        }
    }
    this-> slotUsed = 0;
}

void Inventory::showInventory()
{
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 9; j++){
            string curItem = slot[i][j].getName();
            cout << curItem << " ";
        }
        cout << '\n';
    }
}

void Inventory::give(string itemName, int itemQty)
{
    Item thisItem = Item(itemName);
    
    string ctg = findCategoryByName(itemName);

    if(itemQty <= 0) return;

    for(int i = 0; i < 3 && ctg == "NONTOOL";i++){
        for(int j = 0; j < 9; j++){
            if(itemQty <= 0) break;
            
            if (slot[i][j].getName() == itemName && !slot[i][j].isFull()) {
                int remainQty = 64 - slot[i][j].getQuantity();
                int addQty = min(itemQty, remainQty);

                slot[i][j].setQuantity(slot[i][j].getQuantity() + addQty);
                itemQty -= remainQty;
            }
        }
    }

    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 9; j++){
            if(itemQty <= 0) break;

            if(ctg == "NONTOOL" && slot[i][j].isEmpty()){
                int addQty = min(64, itemQty);
                slot[i][j] = NonTool(itemName, addQty);
                
                this->slotUsed++;
                itemQty -= addQty;
            } 

            if(ctg == "TOOL" && slot[i][j].isEmpty()){
                slot[i][j] = Tool(itemName);
                
                this->slotUsed++;
                itemQty--;
            } 
        }
    }
}

void discard(string slotId, int itemQty)
{
    //TODO
}

void move(string srcSlot, int itemQty, vector<string> destSlot)
{
    //TODO
}

void moveItoC(string srcSlot, vector<string> destSlot)
{
    //TODO
}

void moveItoI(string srcSlot, string destSlot)
{
    //TODO
}

void moveCtoI(string srcSlot, string destSlot)
{
    //TODO
}

void exportFile()
{
    //TODO
}

bool isFull()
{
    
}