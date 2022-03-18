#include <iostream>
#include "../header/inventory.hpp"

using namespace std;

Inventory::Inventory()
{
    for(int i = 0; i < ROWSLOT;i++){
        for(int j = 0; j < COLSLOT; j++){
            this->slot[i][j] = Item();
        }
    }
    this-> slotUsed = 0;
}

void Inventory::showInventory()
{
    for(int i = 0; i < ROWSLOT;i++){
        for(int j = 0; j < COLSLOT; j++){
            string curItem = slot[i][j].getName();
            cout << curItem << " ";
        }
        cout << '\n';
    }
}

void Inventory::give(string itemName, int itemQty)
{
    if (itemQty < 0){
        return; //TODO THROW jumlah item tidak boleh negatif
    }
    if (itemQty == 0) return;
    
    string configPath = "../../config";
    string fileName = "item.txt";
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);
    string ctg = readItemConfig.findCategoryByName(itemName);

    Item thisItem = Item(itemName); 

    for(int i = 0; i < ROWSLOT && itemQty > 0;i++){
        for(int j = 0; j < COLSLOT && itemQty > 0; j++){          
            if (ctg == "NONTOOL" && slot[i][j].getName() == itemName && !slot[i][j].isFull()) {
                int remainQty = 64 - slot[i][j].getQuantity();
                int addQty = min(itemQty, remainQty);

                slot[i][j].setQuantity(slot[i][j].getQuantity() + addQty);
                itemQty -= remainQty;
            }
        }
    }

    for(int i = 0; i < ROWSLOT && itemQty > 0;i++){
        for(int j = 0; j < COLSLOT && itemQty > 0; j++){
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

void Inventory::discard(string slotId, int itemQty)
{
    slotId.erase(0,1); 
    int idNum = stoi(slotId);

    int row = idNum/COLSLOT;
    int col = idNum%COLSLOT;

    if (row < 0 || col < 0 || row >= ROWSLOT || col >= COLSLOT) {
        return; //TODO THROW out of index slot
    }

    if (slot[row][col].isNothing()){
        return; //TODO THROW slot kosong
    }

    if (itemQty < 0){
        return; //TODO THROW jumlah item tidak boleh negatif
    }
    
    if (itemQty == 0) return;

    if ((slot[row][col].getCategory() == "TOOL" && itemQty > 1) ||
        (slot[row][col].getCategory() == "NONTOOL" && itemQty > slot[row][col].getQuantity())
    ){
        return; //TODO THROW jumlah item yang dibuang melebihi kapasitas
    }

    if ((slot[row][col].getCategory() == "TOOL") || 
        (slot[row][col].getCategory() == "NONTOOL" && itemQty == slot[row][col].getQuantity())
    ) slot[row][col] = Item();

    slot[row][col].setQuantity(slot[row][col].getQuantity() - itemQty);
}

void Inventory::move(string srcSlot, int itemQty, vector<string> destSlot)
{
    int src = stoi(srcSlot);

    Slot ssrc = locateSlot(src);
    Item isrc = locateSlot(src).getItem();

    int ndes = destSlot.size();
    int des[ndes];
    for(int i = 0; i < ndes; i++){
        des[i] = stoi(destSlot[i]);
    }

    for(int i = 0; i < ndes; i++){
        if (isrc.getCategory() == "TOOL"){
            Slot slotdes = locateSlot(des[i]);
            if(slotdes.isEmpty()){
                slotdes = Slot(isrc,ssrc.getQuantity());
                discard(srcSlot,ssrc.getQuantity());
            }

            //ASUMSI LOKASI PILIHAN SELALU KOSONG
        }
        if (isrc.getCategory() != "TOOL"){
            Slot slotdes = locateSlot(des[i]);

            if(slotdes.isEmpty()){
                slot[des[i] / 9][des[i] % 9] = Slot(isrc,ssrc.getQuantity());
                discard(srcSlot ,ssrc.getQuantity());
            }
            else{
                if(isrc.getName() != slotdes.getItem().getName()){
                    return; //BEDA BARANG
                }
                if(isrc.getName() == slotdes.getItem().getName()){
                    if(itemQty + slotdes.getItem().getQuantity() > 64){
                        int remainder = (itemQty + slotdes.getItem().getQuantity()) - 64;
                        slot[des[i] / 9][des[i] % 9].getItem().setQuantity(64);
                        slot[src / 9][src % 9].getItem().setQuantity(remainder);
                    }
                    if(itemQty + slotdes.getItem().getQuantity() <= 64){
                        slot[des[i] / 9][des[i] % 9].getItem().setQuantity(slotdes.getItem().getQuantity()+itemQty);
                        slot[src / 9][src % 9].getItem().setQuantity(ssrc.getItem().getQuantity() - itemQty);
                    }
                }
            }
        }
    }
    // for(int i = 0; i < des.lengt)
    //TODO

}

void Inventory::moveItoC(string srcSlot, vector<string> destSlot)
{
    //TODO
}

void Inventory::moveItoI(string srcSlot, string destSlot)
{
    //TODO
}

void Inventory::moveCtoI(string srcSlot, string destSlot)
{
    //TODO
}

Slot Inventory::locateSlot(int slotKe){
    // return this->slot[slotKe / 9][(slotKe % 9)-1]; KALO PENGEN SLOT PERTAMA ITU i1 BUKAN i0
    return this->slot[slotKe / 9][slotKe % 9];
}

void Inventory::exportFile()
{
    //TODO
}

int Inventory::countItem(string itemName) const
{   
    int count = 0;
    for(int i=0; i < ROWSLOT; i++){
        for(int j=0; j < COLSLOT; j++){
            if(!slot[i][j].isNothing() && slot[i][j].getName() == itemName){
                if(slot[i][j].getCategory() == "TOOL") count ++;
                else count += slot[i][j].getQuantity();
            }
        }
    }
    return count;
}

bool Inventory::isFull() const
{
    for(int i=0; i < ROWSLOT; i++){
        for(int j=0; j < COLSLOT; j++){
            if(slot[i][j].isNothing()) return false;
        }
    }
    return true;
}