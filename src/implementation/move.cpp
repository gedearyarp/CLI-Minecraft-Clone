#include "../header/move.hpp"

using namespace std;


void Move::moveItoI(Inventory& inv, string srcSlot, int justInput, string destSlot)
{
    ItemConfig readItemConfig = ItemConfig("./config","item.txt");
    int src = stoi(srcSlot.substr(1));
    int srow = src/COLSLOT;
    int scol = src%COLSLOT;
    Item isrc = inv.locateSlot(src);
    int des = stoi(destSlot.substr(1));
    int drow = des / COLSLOT;
    int dcol = des % COLSLOT;

    if (drow < 0 || drow >= ROWSLOT) {
        throw new IndexOutOfRangeException(drow);
    }

    if (dcol < 0 || dcol >= COLSLOT) {
        throw new IndexOutOfRangeException(dcol);
    }

    // if (itemQty < 0){
        
    //     throw new InvalidQuantityException(itemQty);
    // }
    
   // if (itemQty == 0) return;

    if (srow < 0 || srow >= ROWSLOT) {
        throw new IndexOutOfRangeException(srow);
    }

    if (scol < 0 || scol >= COLSLOT) {
        throw new IndexOutOfRangeException(scol);
    }

    if (inv.locateSlot(9*srow + scol).isNothing()){
        throw new EmptySlotException(srow, scol);
    }

    if (isrc.getCategory() == "TOOL"){
        Item slotdes = inv.locateSlot(des);
        if(slotdes.isEmpty()){
            inv.setSlot(des, new Tool(readItemConfig.findIdByName(isrc.getName()),isrc.getName(),isrc.getDurability()));
            inv.discard(srcSlot,1);
        }
        else
        {
            throw new InvalidDestinationSlot(des);
        }
        
        //ASUMSI LOKASI PILIHAN SELALU KOSONG UNTUK TOOL
    }
    if (isrc.getCategory() != "TOOL"){
        Item slotdes = inv.locateSlot(des);
        int itemQty = inv.slotItem(src)->getQuantity();
        if(slotdes.isEmpty()){
            inv.setSlot(des, new NonTool(isrc.getId(), isrc.getName(), isrc.getType(), itemQty));
            inv.discard(srcSlot ,itemQty);
        }
        else{
        
            if(isrc.getName() != slotdes.getName()){
                return; //BEDA BARANG
            }
            if(isrc.getName() == slotdes.getName()){
                if(itemQty + inv.slotItem(des)->getQuantity() > MAXQTY){
                    int remainder = (inv.slotItem(des)->getQuantity() + inv.slotItem(src)->getQuantity()) - MAXQTY;
                    inv.slotItem(des)->setQuantity(MAXQTY);
                    inv.slotItem(src)->setQuantity(remainder);
                }
                if (itemQty + inv.slotItem(des)->getQuantity() <= MAXQTY)
                {

                    inv.slotItem(des)->setQuantity(inv.slotItem(des)->getQuantity()+itemQty);
                    
                    inv.discard(srcSlot, itemQty);
                }
            }
        }
    }
}

void Move::moveItoC(Inventory& inv, string srcSlot, int justParam, string destSlot, CraftingTable& craft)
{
    ItemConfig readItemConfig = ItemConfig("./config","item.txt");
    int src = stoi(srcSlot.substr(1));
    int srow = src/COLSLOT;
    int scol = src%COLSLOT;
    Item *isrc = inv.slotItem(src);
    int des = stoi(destSlot.substr(1));
    int drow = des/3;
    int dcol = des%3;
    Item ides =  craft.getSlot(des);

    if (justParam < 0){
        throw new InvalidQuantityException(justParam);
    }
    
    if (justParam == 0) return;

    if (srow < 0 || srow >= ROWSLOT) {
        throw new IndexOutOfRangeException(srow);
    }

    if (scol < 0 || scol >= COLSLOT) {
        throw new IndexOutOfRangeException(scol);
    }

    if (drow < 0 || drow >= 3) {
        throw new IndexOutOfRangeException(drow);
    }

    if (dcol < 0 || dcol >= 3) {
        throw new IndexOutOfRangeException(dcol);
    }

    if (inv.locateSlot(9*srow + scol).isNothing()){
        throw new EmptySlotException(srow, scol);
    }

    if (isrc->getCategory() == "TOOL"){
        if(craft.getSlot(des).isEmpty()){
            craft.setSlot(des, new Tool(isrc->getId(), isrc->getName(), isrc->getDurability()));
            inv.discardAll(srcSlot);
        }
        else {
            throw new InvalidDestinationSlot(des);
            //Destinasi tool harus kosong
        }
    }
    if (isrc->getCategory() != "TOOL"){
        int itemQty = 1;
        if(craft.getSlot(des).isEmpty()){
            craft.setSlot(des, new NonTool(isrc->getId(), isrc->getName(), isrc->getType(), 1));
            inv.discard(srcSlot,1);
        }
        else{
            //gabisa dulu soalnya sementara di crafting tabel maksimal 1

            // if(isrc.getName() != ides.getName()){
            //     throw new InvalidDestinationSlot(des);
            //     //BEDA BARANG
            // }
            // if(isrc.getName() == ides.getName()){
            //     if(itemQty + ides.getQuantity() > MAXQTY){
            //         int remainder = (inv.slotItem(des)->getQuantity() + inv.slotItem(src)->getQuantity()) - MAXQTY;
            //         craft.setSlot(des, NonTool(isrc.getId(), isrc.getName(), isrc.getType(), MAXQTY));
            //         inv.slotItem(src)->setQuantity(remainder);
            //     }
            //     if(itemQty + ides.getQuantity() <= MAXQTY){
            //         craft.setSlot(des, NonTool(isrc.getId(), isrc.getName(), isrc.getType(), itemQty));
            //         inv.discard(srcSlot, itemQty);
            //     }   
            // }
        }
    }
}

void Move::moveCtoI(Inventory& inv, string srcSlot, int justParam, string destSlot, CraftingTable& craft)
{
    ItemConfig readItemConfig = ItemConfig("./config","item.txt");
    int src = stoi(srcSlot.substr(1));
    int srow = src/3;
    int scol = src%3;
    Item *isrc = craft.slotItem(src);
    int des = stoi(destSlot.substr(1));
    int drow = des/COLSLOT;
    int dcol = des%COLSLOT;
    Item *ides = inv.slotItem(des);

    if (justParam < 0){
        throw new InvalidQuantityException(justParam);
    }
    
    if (justParam == 0) return;
    
    if (srow < 0 || srow >= 3) {
        throw new IndexOutOfRangeException(srow);
    }

    if (scol < 0 || scol >= 3) {
        throw new IndexOutOfRangeException(scol);
    }

    if (drow < 0 || drow >= ROWSLOT) {
        throw new IndexOutOfRangeException(drow);
    }

    if (dcol < 0 || dcol >= COLSLOT) {
        throw new IndexOutOfRangeException(dcol);
    }

    if (craft.getSlot(src).isNothing()){
        throw new EmptySlotException(srow, scol);
    }

    if (isrc->getCategory() == "TOOL"){
        if(ides->isEmpty()){
            craft.setSlot(des,new Item());
            inv.setSlot(src, new Tool(readItemConfig.findIdByName(isrc->getName()),isrc->getName(),isrc->getDurability()));
        }
        else {
            throw new InvalidDestinationSlot(des);
            //Destinasi tool harus kosong
        }
    }
    if (isrc->getCategory() != "TOOL"){
        int itemQty = isrc->getQuantity();
        if(ides->isEmpty()){
            craft.setSlot(des, new NonTool(isrc->getId(), isrc->getName(), isrc->getType(), itemQty));
            inv.discard(srcSlot ,itemQty);

            craft.setSlot(src,new NonTool(isrc->getId(), isrc->getName(), isrc->getType(), isrc->getQuantity() - itemQty));
            inv.setSlot(src, new NonTool(isrc->getId(), isrc->getName(), isrc->getType(), itemQty));
            if(isrc->getQuantity()-itemQty <= 0){
                craft.setSlot(src, new Item());
            }
        }
        else{
            if(isrc->getName() != ides->getName()){
                throw new InvalidDestinationSlot(des);
            }
            if(isrc->getName() == ides->getName()){
                if(itemQty + ides->getQuantity() > MAXQTY){
                    int remainder = (isrc->getQuantity() + ides->getQuantity()) - MAXQTY;
                    craft.setSlot(src, new NonTool(isrc->getId(), isrc->getName(), isrc->getType(), remainder));
                    inv.slotItem(src)->setQuantity(MAXQTY);
                }
                if(itemQty + ides->getQuantity() <= MAXQTY){
                    craft.setSlot(src, new NonTool(isrc->getId(), isrc->getName(), isrc->getType(), isrc->getQuantity()-itemQty));
                    if (isrc->getQuantity() - itemQty <= 0)
                    {
                        craft.setSlot(src, new Item());
                    }
                    inv.slotItem(src)->setQuantity(ides->getQuantity() + itemQty);
                }   
            }
        }
    }
}