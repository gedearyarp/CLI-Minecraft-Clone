#include <iostream>
#include "../header/inventory.hpp"
#include "../header/craft.hpp"

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

    Item thisItem = Item(itemName,readItemConfig.getItemConfig()); 

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
                slot[i][j] = NonTool(itemName, addQty, readItemConfig.getItemConfig());
                
                this->slotUsed++;
                itemQty -= addQty;
            } 

            if(ctg == "TOOL" && slot[i][j].isEmpty()){
                slot[i][j] = Tool(itemName, readItemConfig.getItemConfig());
                
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

void Inventory::discardAll(string slotId){
    int slotKe = stoi(slotId);
    slot[slotKe / 9][slotKe % 9] = Item();
}

void Inventory::move(string srcSlot, int itemQty, vector<string> destSlot)
{
    ItemConfig readItemConfig = ItemConfig("../../config","item.txt");
    int src = stoi(srcSlot);
    Item isrc = locateSlot(src);

    int ndes = destSlot.size();
    int des[ndes];

    for(int i = 0; i < ndes; i++){
        des[i] = stoi(destSlot[i]);
    }

    for(int i = 0; i < ndes; i++){
        if (isrc.getCategory() == "TOOL"){
            Item slotdes = locateSlot(des[i]);
            if(slotdes.isEmpty()){
                slot[des[i] / 9][des[i] % 9] = Tool(isrc.getName(),isrc.getDurability(), readItemConfig.getItemConfig());
                discard(srcSlot,isrc.getQuantity());
            }
            //ASUMSI LOKASI PILIHAN SELALU KOSONG UNTUK TOOL
        }
        if (isrc.getCategory() != "TOOL"){
            Item slotdes = locateSlot(des[i]);

            if(slotdes.isEmpty()){
                slot[des[i] / 9][des[i] % 9] = NonTool(isrc.getName(),isrc.getQuantity(), readItemConfig.getItemConfig());
                discard(srcSlot ,isrc.getQuantity());
            }
            else{
                if(isrc.getName() != slotdes.getName()){
                    return; //BEDA BARANG
                }
                if(isrc.getName() == slotdes.getName()){
                    if(itemQty + slotdes.getQuantity() > 64){
                        int remainder = (isrc.getQuantity() + slotdes.getQuantity()) - 64;
                        slot[des[i] / 9][des[i] % 9].setQuantity(64);
                        slot[src / 9][src % 9].setQuantity(remainder);
                        if(slot[src / 9][src % 9].getQuantity() <= 0){
                            discardAll(srcSlot);
                        }
                    }
                    if(itemQty + slotdes.getQuantity() <= 64){
                        slot[des[i] / 9][des[i] % 9].setQuantity(slotdes.getQuantity()+itemQty);
                        slot[src / 9][src % 9].setQuantity(isrc.getQuantity() - itemQty);
                        if(slot[src / 9][src % 9].getQuantity() <= 0){
                            discardAll(srcSlot);
                        }
                    }   
                }
            }
        }
    }
    // for(int i = 0; i < des.lengt)
    //TODO
}

void Inventory::moveItoC(string srcSlot, int itemQty, string destSlot, CraftingTable craft)
{
    ItemConfig readItemConfig = ItemConfig("../../config","item.txt");
    int src = stoi(srcSlot);
    Item isrc = locateSlot(src);
    int des = stoi(destSlot);
    Item ides = craft.getSlot(des);

    // if(ides.isEmpty() && isrc.getCategory() == "NONTOOL"){
    //     craft.setSlot(des, NonTool(isrc.getName(), itemQty, readItemConfig.getItemConfig()));
    //     this->setSlot(src, NonTool(isrc.getName(), isrc.getQuantity()-itemQty, readItemConfig.getItemConfig()));
    //     if(isrc.getQuantity()-itemQty <= 0){
    //         discardAll(srcSlot);
    //     }
    // }

    if (isrc.getCategory() == "TOOL"){
        if(craft.getSlot(des).isEmpty()){
            craft.setSlot(des,isrc);
            this->discardAll(srcSlot);
        }else return;
        //ASUMSI LOKASI PILIHAN SELALU KOSONG UNTUK TOOL
    }
    if (isrc.getCategory() != "TOOL"){
        if(craft.getSlot(des).isEmpty()){
            craft.setSlot(des,NonTool(isrc.getName(), itemQty, readItemConfig.getItemConfig()));
            this->discard(srcSlot ,itemQty);
            if(isrc.getQuantity()-itemQty <= 0){
                this->discardAll(srcSlot);
            }
        }
        else{
            if(isrc.getName() != ides.getName()){
                return; //BEDA BARANG
            }
            if(isrc.getName() == ides.getName()){
                if(itemQty + ides.getQuantity() > 64){
                    int remainder = (isrc.getQuantity() + ides.getQuantity()) - 64;
                    craft.setSlot(des, NonTool(isrc.getName(), 64,readItemConfig.getItemConfig()));
                    this->slot[src / 9][src % 9].setQuantity(remainder);
                }
                if(itemQty + ides.getQuantity() <= 64){
                    craft.setSlot(des, NonTool(isrc.getName(), ides.getQuantity()+itemQty,readItemConfig.getItemConfig()));
                    this->slot[src / 9][src % 9].setQuantity(isrc.getQuantity() - itemQty);
                    if(slot[src / 9][src % 9].getQuantity() <= 0){
                        discardAll(srcSlot);
                    }
                }   
            }
        }
    }

// for(int i = 0; i < des.lengt)
//TODO
    

    //TODO
}

void Inventory::moveItoI(string srcSlot, int itemQty, string destSlot)
{
    //TODO
}

void Inventory::moveCtoI(string srcSlot, int itemQty, string destSlot)
{
    //TODO
}

Item Inventory::locateSlot(int slotKe){
    // return this->slot[slotKe / 9][(slotKe % 9)-1]; KALO PENGEN SLOT PERTAMA ITU i1 BUKAN i0
    return this->slot[slotKe / 9][slotKe % 9];
}

void Inventory::setSlot(int slotKe, Item item) {
    this->slot[slotKe / 9][slotKe % 9] = item;
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