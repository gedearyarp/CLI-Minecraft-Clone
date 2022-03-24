#include "../header/inventory.hpp"

using namespace std;

Inventory::Inventory()
{
    this->slot = vector<vector<Item*>>(ROWSLOT, vector<Item*>(COLSLOT, new Item()));
    this-> slotUsed = 0;
}

void Inventory::showInventory()
{
    for(int i = 0; i < ROWSLOT;i++){
        for(int j = 0; j < COLSLOT; j++){
            string nameTool = "TOOL";
            string curItem = slot[i][j]->getName();
            int curQty = slot[i][j]->getQuantity();
            cout << "[ " <<curItem << " " << curQty ;
            if(slot[i][j]->getCategory().compare(0,4,nameTool,0,4) == 0)
            {
                cout << " " << slot[i][j]->getDurability();
            }
            cout << "] ";
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

    for(int i = 0; i < ROWSLOT && itemQty > 0;i++){
        for(int j = 0; j < COLSLOT && itemQty > 0; j++){
            if (ctg == "NONTOOL" && slot[i][j]->isEmpty() && itemQty > 0)
            {
                cout << slot[i][j]->getQuantity() << endl;
                int addQty = min(MAXQTY, itemQty);
                NonTool *NT = new NonTool(readItemConfig.findIdByName(itemName), itemName, readItemConfig.findTypeByName(itemName), addQty);
                slot[i][j] = NT;

                this->slotUsed++;
                itemQty -= addQty;
            }

            else if (ctg == "TOOL" && slot[i][j]->isEmpty() && itemQty > 0)
            {
                Tool *T = new Tool(readItemConfig.findIdByName(itemName), itemName);
                slot[i][j] = T;

                this->slotUsed++;
                itemQty--;
            }
        }
    }

    for(int i = 0; i < ROWSLOT && itemQty > 0;i++){
        for(int j = 0; j < COLSLOT && itemQty > 0; j++){
            if (ctg == "NONTOOL" && slot[i][j]->getName() == itemName && !slot[i][j]->isFull())
            {
                int remainQty = MAXQTY - slot[i][j]->getQuantity();
                int addQty = min(itemQty, remainQty);
                slot[i][j]->setQuantity(slot[i][j]->getQuantity() + addQty);
                itemQty -= remainQty;
            }
        }
    }
    
}

void Inventory::giveToolWithDurability(string itemName, int itemQty, int durability)
{
    if (itemQty < 0){
        throw new InvalidQuantityException(itemQty);
    }

    if (itemQty == 0) return;
    
    string configPath = "./config";
    string fileName = "item.txt";
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);
    string ctg = readItemConfig.findCategoryByName(itemName);

    if (ctg != "TOOL")
    {
        throw new InvalidCategoryException(ctg);
    }

    for(int i = 0; i < ROWSLOT && itemQty > 0;i++){
        for(int j = 0; j < COLSLOT && itemQty > 0; j++){
            if (ctg == "TOOL" && slot[i][j]->isEmpty() && itemQty > 0)
            {
                Tool *T = new Tool(readItemConfig.findIdByName(itemName), itemName, durability);
                slot[i][j] = T;

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

    if (slot[row][col]->isNothing()){
        throw new EmptySlotException(row, col);
    }

    if (itemQty < 0){
        throw new InvalidQuantityException(itemQty);
    }
    
    if (itemQty == 0) return;

    if ((slot[row][col]->getCategory() == "TOOL" && itemQty > 1) ||
        (slot[row][col]->getCategory() == "NONTOOL" && itemQty > slot[row][col]->getQuantity())
    ){
        throw new DiscardQuantityException(
            itemQty,
            (slot[row][col]->getCategory() == "TOOL") ? 1 : (slot[row][col]->getQuantity())
        );
    }

    if ((slot[row][col]->getCategory() == "TOOL") || 
        (slot[row][col]->getCategory() == "NONTOOL" && itemQty == slot[row][col]->getQuantity())
    ) slot[row][col] = new Item();

    slot[row][col]->setQuantity(slot[row][col]->getQuantity() - itemQty);
}

void Inventory::discardAll(string slotId){
    int slotKe = stoi(slotId.substr(1));
    slot[slotKe / COLSLOT][slotKe % COLSLOT] = new Item();
}

void Inventory::importFile()
{
    string inventoryPath = "./config/inventory/inventory.txt";
    ifstream inv(inventoryPath);
    string line;

    string configPath = "./config";
    string fileName = "item.txt";
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);

    if(inv.is_open()) {
        int idx = 0;
        while(getline(inv, line) && idx < 27){
            if (line == "0:0" || line[0] == '0') {
                setSlot(idx, new Item());
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
                qty = stoi(qtyItem);
            } catch(exception &err) {
                throw new InvalidInventoryTextException(line);
            }
            
            if (id < 1 || id > 38) {
                throw new IndexOutOfRangeException(id);
            }

            string ctg = readItemConfig.findCategoryById(id);
            if (ctg == "NONTOOL" && (qty < 1 || qty > MAXQTY)
            ) {
                throw new InvalidQuantityException(qty);
            }

            if (ctg != "NONTOOL" && ctg != "TOOL"){
                throw new CustomException(ctg);
            }

            string itemName = readItemConfig.findNameById(id);

            if (ctg == "TOOL") {
                Tool* newSlot = new Tool(id, itemName, qty);
                setSlot(idx, newSlot);
            } 
            else {
                NonTool* newSlot = new NonTool(id, itemName, readItemConfig.findTypeByName(itemName), qty);
                setSlot(idx, newSlot);
            } 
            
            idx++;
        }

        inv.close();
    } else {
        throw new OpenFileErrorException(fileName);
    }
}

void Inventory::exportFile(){
    ofstream fout;
    string filePath = "./tests/res.out";
    fout.open(filePath);
    for(int i=0; i<27; i++){
        if(slotItem(i)->isNothing()){
            fout << "0:0" << endl;
        }
        else if(slotItem(i)->getCategory() == "TOOL"){
            fout << slotItem(i)->getId() << ":" << slotItem(i)->getDurability() << endl;
        } else {
            fout << slotItem(i)->getId() << ":" << slotItem(i)->getQuantity() << endl;
        }
    }
    fout.close();
}

Item Inventory::locateSlot(int slotKe){
    return *this->slot[slotKe / COLSLOT][slotKe % COLSLOT];
}

void Inventory::setSlot(int slotKe, Item* item) {
    this->slot[slotKe / COLSLOT][slotKe % COLSLOT] = item;
}

Item*& Inventory::slotItem(int slotKe)
{
    return this->slot[slotKe / COLSLOT][slotKe % COLSLOT];
}

int Inventory::countItem(string itemName) const
{   
    int count = 0;
    for(int i=0; i < ROWSLOT; i++){
        for(int j=0; j < COLSLOT; j++){
            if(!slot[i][j]->isNothing() && slot[i][j]->getName() == itemName){
                if(slot[i][j]->getCategory() == "TOOL") count ++;
                else count += slot[i][j]->getQuantity();
            }
        }
    }
    return count;
}

bool Inventory::isFull() const
{
    for(int i=0; i < ROWSLOT; i++){
        for(int j=0; j < COLSLOT; j++){
            if(slot[i][j]->isNothing()) return false;
        }
    }
    return true;
}

void Inventory::use(string srcSlot)
{
    srcSlot = srcSlot.erase(0, 1);
    int src;

    try {
        src = stoi(srcSlot);
    } catch(exception &err) {
        throw new CustomException("stoi error");
    }

    if (slotItem(src)->getCategory() == "TOOL")
    {
        int durability = slotItem(src)->getDurability();
        slotItem(src)->setDurability(durability - 1);
        if(durability - 1 <= 0) 
        {
            discardAll(srcSlot);
        }
    }
    else
    {
        throw new InvalidCategoryException(slotItem(src)->getCategory());
    }
}