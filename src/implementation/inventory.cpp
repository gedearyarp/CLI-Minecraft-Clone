#include "../header/inventory.hpp"
#include <iostream>
using namespace std;

Slot::Slot()
{
    this-> item = Item();
    this-> quantity = 0;
}

Slot::Slot(Item item, int qty)
{
    this->item = item;
    this-> quantity = qty;
}

Slot::Slot(string item, int qty)
{
    Item newItem = Item(item);
    this->item = newItem;
    this-> quantity = qty;
}

void Slot::addItemSlot(int qty)
{
    this->quantity += qty;
}

void Slot::discardItemSlot(int qty)
{
    this->quantity -= qty;
}

int Slot::getQuantity()
{
    return this->quantity;
}

Item Slot::getItem()
{
    return this->item;
}

bool Slot::isTool()
{
    return (this->item.get_category() == "TOOL");
}

bool Slot::isEmpty()
{
    return (this->quantity == 0);
}

Inventory:: Inventory()
{
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 9; j++){
            this->slot[i][j] = Slot();
        }
    }
    this-> slotUsed = 0;
}

void Inventory::showInventory()
{
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 9; j++){
            string curItem = slot[i][j].getItem().get_name();
            cout << curItem << " ";
        }
        cout << '\n';
    }
}

void Inventory::give(string itemName, int itemQty)
{
    Item thisItem = Item(itemName);
    bool thisIsTool = (thisItem.get_category() != "TOOL");
    if(itemQty <= 0) return;

    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 9; j++){
            if(itemQty <= 0) break;
            
            if (!thisIsTool && slot[i][j].getItem().get_name() == itemName && !slot[i][j].isFull()) {
                int remainQty = 64 - slot[i][j].getQuantity();
                int addQty = min(itemQty, remainQty);

                slot[i][j].addItemSlot(addQty);
                itemQty -= remainQty;
            }
        }
    }

    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 9; j++){
            if(itemQty <= 0) break;

            if(slot[i][j].isEmpty() && !thisIsTool){
                NonTool newItem = NonTool(itemName);
                int addQty = min(64, itemQty);
                slot[i][j] = Slot(newItem, addQty);
                
                this->slotUsed++;
                itemQty -= addQty;
            } 

            if(slot[i][j].isEmpty() && thisIsTool){
                Tool newItem = Tool(itemName);
                slot[i][j] = Slot(newItem, 1);
                
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