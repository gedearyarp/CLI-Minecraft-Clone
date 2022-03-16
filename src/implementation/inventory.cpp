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

void Slot::addItemSlot(int qty)
{

}

void Slot::discardItemSlot(int qty)
{

}

int Slot::getQuantity(Slot slot)
{
    return slot.quantity;
}

Item Slot::getItem(Slot slot)
{
    return slot.item;
}

bool Slot::isTool(Slot slot)
{
    //Harus nambah isTool di item soalnya categorynya private
    // return(slot.item.category == "TOOL");
}

bool Slot::isEmpty(Slot slot)
{
    return (slot.quantity == 0);
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
            cout << curItem;
        }
    }
}

void Inventory::give(string itemName, int itemQty)
{
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 9; j++){
            if(isEmpty(slot[i][j])){
                slot[i][j].item.name = itemName;
                slot[i][j].quantity += itemQty;
                break;
            }
            }
    }
}

void discard(string slotId, int itemQty)
{

}

void move(string srcSlot, int itemQty, vector<string> destSlot)
{

}

void moveItoC(string srcSlot, vector<string> destSlot)
{

}

void moveItoI(string srcSlot, string destSlot)
{

}

void moveCtoI(string srcSlot, string destSlot)
{

}

void exportFile()
{

}

bool isFull()
{
    
}