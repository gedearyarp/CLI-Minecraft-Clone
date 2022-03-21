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

Slot Inventory::locateSlot(int slotKe){
    // return this->slot[slotKe / 9][(slotKe % 9)-1]; KALO PENGEN SLOT PERTAMA ITU i1 BUKAN i0
    return this->slot[slotKe / 9][slotKe % 9];
}