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
        throw new InvalidQuantityException(itemQty);
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
                int remainQty = MAXQTY - slot[i][j].getQuantity();
                int addQty = min(itemQty, remainQty);

                slot[i][j].setQuantity(slot[i][j].getQuantity() + addQty);
                itemQty -= remainQty;
            }
        }
    }

    for(int i = 0; i < ROWSLOT && itemQty > 0;i++){
        for(int j = 0; j < COLSLOT && itemQty > 0; j++){
            if(ctg == "NONTOOL" && slot[i][j].isEmpty()){
                int addQty = min(MAXQTY, itemQty);
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

    if (row < 0 || row >= ROWSLOT) {
        throw new IndexOutOfRangeException(row);
    }

    if (col < 0 || col >= COLSLOT) {
        throw new IndexOutOfRangeException(col);
    }

    if (slot[row][col].isNothing()){
        throw new EmptySlotException(row, col);
    }

    if (itemQty < 0){
        throw new InvalidQuantityException(itemQty);
    }
    
    if (itemQty == 0) return;

    if ((slot[row][col].getCategory() == "TOOL" && itemQty > 1) ||
        (slot[row][col].getCategory() == "NONTOOL" && itemQty > slot[row][col].getQuantity())
    ){
        throw new DiscardQuantityException(
            itemQty,
            (slot[row][col].getCategory() == "TOOL") ? 1 : (slot[row][col].getQuantity())
        );
    }

    if ((slot[row][col].getCategory() == "TOOL") || 
        (slot[row][col].getCategory() == "NONTOOL" && itemQty == slot[row][col].getQuantity())
    ) slot[row][col] = Item();

    slot[row][col].setQuantity(slot[row][col].getQuantity() - itemQty);
}

void Inventory::discardAll(string slotId){
    int slotKe = stoi(slotId);
    slot[slotKe / COLSLOT][slotKe % COLSLOT] = Item();
}

void Inventory::moveItoI(string srcSlot, int itemQty, vector<string> destSlot)
{
    ItemConfig readItemConfig = ItemConfig("../../config","item.txt");
    int src = stoi(srcSlot);
    int srow = src/COLSLOT;
    int scol = src%COLSLOT;
    Item isrc = locateSlot(src);

    int ndes = destSlot.size();
    int des[ndes];

    for(int i = 0; i < ndes; i++)
    {
        int drow = stoi(destSlot[i]) / COLSLOT;
        int dcol = stoi(destSlot[i]) % COLSLOT;
        if (drow < 0 || drow >= ROWSLOT) {
            throw new IndexOutOfRangeException(drow);
        }

        if (dcol < 0 || dcol >= COLSLOT) {
            throw new IndexOutOfRangeException(dcol);
        }
        des[i] = stoi(destSlot[i]);
    }

    if (itemQty < 0){
        throw new InvalidQuantityException(itemQty);
    }
    
    if (itemQty == 0) return;

    if (srow < 0 || srow >= ROWSLOT) {
        throw new IndexOutOfRangeException(srow);
    }

    if (scol < 0 || scol >= COLSLOT) {
        throw new IndexOutOfRangeException(scol);
    }

    if (slot[srow][scol].isNothing()){
        throw new EmptySlotException(srow, scol);
    }

    for(int i = 0; i < ndes; i++){
        if (isrc.getCategory() == "TOOL"){
            Item slotdes = locateSlot(des[i]);
            if(slotdes.isEmpty()){
                slot[des[i] / COLSLOT][des[i] % COLSLOT] = Tool(isrc.getName(),isrc.getDurability(), readItemConfig.getItemConfig());
                discard(srcSlot,isrc.getQuantity());
            }
            throw new InvalidDestinationSlot(des[i]);
            //ASUMSI LOKASI PILIHAN SELALU KOSONG UNTUK TOOL
        }
        if (isrc.getCategory() != "TOOL"){
            Item slotdes = locateSlot(des[i]);

            if(slotdes.isEmpty()){
                slot[des[i] / COLSLOT][des[i] % COLSLOT] = NonTool(isrc.getName(),isrc.getQuantity(), readItemConfig.getItemConfig());
                discard(srcSlot ,isrc.getQuantity());
            }
            else{
                if(isrc.getName() != slotdes.getName()){
                    return; //BEDA BARANG
                }
                if(isrc.getName() == slotdes.getName()){
                    if(itemQty + slotdes.getQuantity() > MAXQTY){
                        int remainder = (isrc.getQuantity() + slotdes.getQuantity()) - MAXQTY;
                        slot[des[i] / COLSLOT][des[i] % COLSLOT].setQuantity(MAXQTY);
                        slot[src / COLSLOT][src % COLSLOT].setQuantity(remainder);
                        if(slot[src / COLSLOT][src % COLSLOT].getQuantity() <= 0){
                            discardAll(srcSlot);
                        }
                    }
                    if(itemQty + slotdes.getQuantity() <= MAXQTY){
                        slot[des[i] / COLSLOT][des[i] % COLSLOT].setQuantity(slotdes.getQuantity()+itemQty);
                        slot[src / COLSLOT][src % COLSLOT].setQuantity(isrc.getQuantity() - itemQty);
                        if(slot[src / COLSLOT][src % COLSLOT].getQuantity() <= 0){
                            discardAll(srcSlot);
                        }
                    }   
                }
            }
        }
    }
}

void Inventory::moveItoC(string srcSlot, int itemQty, string destSlot, CraftingTable craft)
{
    
    ItemConfig readItemConfig = ItemConfig("../../config","item.txt");
    int src = stoi(srcSlot);
    int srow = src/COLSLOT;
    int scol = src%COLSLOT;
    Item isrc = locateSlot(src);
    int des = stoi(destSlot);
    int drow = des/3;
    int dcol = des%3;
    Item ides = craft.getSlot(des);

    if (itemQty < 0){
        throw new InvalidQuantityException(itemQty);
    }
    
    if (itemQty == 0) return;

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

    if (slot[srow][scol].isNothing()){
        throw new EmptySlotException(srow, scol);
    }

    if (isrc.getCategory() == "TOOL"){
        if(craft.getSlot(des).isEmpty()){
            craft.setSlot(des,isrc);
            this->discardAll(srcSlot);
        }
        else {
            throw new InvalidDestinationSlot(des);
            //Destinasi tool harus kosong
        }
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
                throw new InvalidDestinationSlot(des);
                //BEDA BARANG
            }
            if(isrc.getName() == ides.getName()){
                if(itemQty + ides.getQuantity() > MAXQTY){
                    int remainder = (isrc.getQuantity() + ides.getQuantity()) - MAXQTY;
                    craft.setSlot(des, NonTool(isrc.getName(), MAXQTY,readItemConfig.getItemConfig()));
                    this->slot[src / COLSLOT][src % COLSLOT].setQuantity(remainder);
                }
                if(itemQty + ides.getQuantity() <= MAXQTY){
                    craft.setSlot(des, NonTool(isrc.getName(), ides.getQuantity()+itemQty,readItemConfig.getItemConfig()));
                    this->slot[src / COLSLOT][src % COLSLOT].setQuantity(isrc.getQuantity() - itemQty);
                    if(slot[src / COLSLOT][src % COLSLOT].getQuantity() <= 0){
                        this->discardAll(srcSlot);
                    }
                }   
            }
        }
    }
}

void Inventory::moveCtoI(string srcSlot, int itemQty, string destSlot, CraftingTable craft)
{
    ItemConfig readItemConfig = ItemConfig("../../config","item.txt");
    int src = stoi(srcSlot);
    int srow = src/3;
    int scol = src%3;
    Item isrc = craft.getSlot(src);
    int des = stoi(destSlot);
    int drow = des/COLSLOT;
    int dcol = des%COLSLOT;
    Item ides = locateSlot(des);

    if (itemQty < 0){
        throw new InvalidQuantityException(itemQty);
    }
    
    if (itemQty == 0) return;
    
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

    if (isrc.getCategory() == "TOOL"){
        if(ides.isEmpty()){
            craft.setSlot(des,Item());
            this->slot[src / COLSLOT][src % COLSLOT] = Tool(isrc.getName(), isrc.getDurability(),readItemConfig.getItemConfig());
        }
        else {
            throw new InvalidDestinationSlot(des);
            //Destinasi tool harus kosong
        }
    }
    if (isrc.getCategory() != "TOOL"){
        if(ides.isEmpty()){
            craft.setSlot(des,NonTool(isrc.getName(), itemQty, readItemConfig.getItemConfig()));
            this->discard(srcSlot ,itemQty);

            craft.setSlot(src,NonTool(isrc.getName(), isrc.getQuantity() - itemQty, readItemConfig.getItemConfig()));
            this->slot[src / COLSLOT][src % COLSLOT] = NonTool(isrc.getName(), itemQty, readItemConfig.getItemConfig());
            if(isrc.getQuantity()-itemQty <= 0){
                craft.setSlot(src, Item());
            }
        }
        else{
            if(isrc.getName() != ides.getName()){
                throw new InvalidDestinationSlot(des);
            }
            if(isrc.getName() == ides.getName()){
                if(itemQty + ides.getQuantity() > MAXQTY){
                    int remainder = (isrc.getQuantity() + ides.getQuantity()) - MAXQTY;
                    craft.setSlot(src, NonTool(isrc.getName(), remainder ,readItemConfig.getItemConfig()));
                    this->slot[src / COLSLOT][src % COLSLOT].setQuantity(MAXQTY);
                }
                if(itemQty + ides.getQuantity() <= MAXQTY){
                    craft.setSlot(src, NonTool(isrc.getName(), isrc.getQuantity()-itemQty,readItemConfig.getItemConfig()));
                    this->slot[des / COLSLOT][des % COLSLOT].setQuantity(ides.getQuantity() + itemQty);
                    if(slot[src / COLSLOT][src % COLSLOT].getQuantity() <= 0){
                        this->discardAll(srcSlot);
                    }
                }   
            }
        }
    }
}

void Inventory::exportFile()
{
    string inventoryPath = "../../config/inventory/inventory.txt";
    ifstream inv(inventoryPath);
    string line;

    string configPath = "../../config";
    string fileName = "item.txt";
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);

    if(inv.is_open()) {
        for(int idx = 0; idx < MAXINV; idx++){
            if (line == "0:0") {
                setSlot(idx, Item());
                idx++;
                continue;
            } 

            string idItem = "", qtyItem = ""; 
            bool flag = false;
            
            for(int i=0; i < line.size(); i++){
                if(line[i] == ':'){
                    flag = true;
                    continue;
                }

                if(flag) qtyItem += line[i];
                else idItem += line[i];
            }

            if (!flag) {
                throw new InvalidInventoryTextException(line);
            }

            int id, qty;
            try {
                id = stoi(idItem);
                qty = stoi(idItem);
            } catch(exception &err) {
                throw new InvalidInventoryTextException(line);
            }
            
            if (id < 1 || id > MAXINV) {
                throw new IndexOutOfRangeException(id);
            }

            string ctg = readItemConfig.findCategoryById(id);
            if ((ctg == "TOOL" && qty != 1) ||
                (ctg == "NONTOOL" && (qty < 1 || qty > MAXQTY))
            ) {
                throw new InvalidQuantityException(qty);
            }

            string itemName = readItemConfig.findNameById(id);
            Item newSlot;

            if (ctg == "TOOL") newSlot = Tool(itemName, readItemConfig.getItemConfig());
            else newSlot = NonTool(itemName, qty, readItemConfig.getItemConfig());

            setSlot(idx, newSlot);
        }

        inv.close();
    } else {
        throw new OpenFileErrorException(fileName);
    }
}

Item Inventory::locateSlot(int slotKe){
    return this->slot[slotKe / COLSLOT][slotKe % COLSLOT];
}

void Inventory::setSlot(int slotKe, Item item) {
    this->slot[slotKe / COLSLOT][slotKe % COLSLOT] = item;
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

void Inventory::use(string srcSlot)
{
    int src = stoi(srcSlot);
    if (this->slot[src / COLSLOT][src % COLSLOT].getCategory() == "TOOL")
    {
        int durability = this->slot[src / COLSLOT][src % COLSLOT].getDurability();
        this->slot[src / COLSLOT][src % COLSLOT].setDurability(durability -1);
        if(durability - 1 <= 0)
        {
            discardAll(srcSlot);
        }
    }
    else
    {
        throw "INVALID TYPE";
    }
}