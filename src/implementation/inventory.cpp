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
    
    string configPath = "./config";
    string fileName = "item.txt";
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);
    string ctg = readItemConfig.findCategoryByName(itemName);

    Item thisItem = Item(readItemConfig.findIdByName(itemName),itemName,readItemConfig.findTypeByName(itemName),readItemConfig.findCategoryByName(itemName)); 

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
                slot[i][j] = NonTool(readItemConfig.findIdByName(itemName),itemName, readItemConfig.findTypeByName(itemName), addQty);
                
                this->slotUsed++;
                itemQty -= addQty;
            } 

            if(ctg == "TOOL" && slot[i][j].isEmpty()){
                slot[i][j] = Tool(readItemConfig.findIdByName(itemName),itemName);
                
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

void Inventory::exportFile()
{
    string inventoryPath = "./config/inventory/inventory.txt";
    ifstream inv(inventoryPath);
    string line;

    string configPath = "./config";
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

            if (ctg == "TOOL") newSlot = Tool(readItemConfig.findIdByName(itemName),itemName);
            else newSlot = NonTool(readItemConfig.findIdByName(itemName),itemName, readItemConfig.findTypeByName(itemName), qty);

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