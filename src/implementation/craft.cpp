#include "../header/craft.hpp"

using namespace std;

template<class T>
CraftingTable<T>::CraftingTable() {
    this->Table = new T[3][3];
}

template<class T>
void CraftingTable<T>::PutItemToCraftingTableFromInventory(string craftingSlotId, int amount, string InventorySlotId){
    // TODO
}

template<class T>
bool CraftingTable<T>::EligibleForCrafting() const {
    // TODO
}

template<class T>
void CraftingTable<T>::Craft() {
    // TODO
}

template<class T>
void CraftingTable<T>::PutItemToInventoryFromCraftingTable(string InventorySlotId, int amount, string craftingSlotId) {\
    // TODO
}

template<class T>
void CraftingTable<T>::showTable() {
    // TODO
    cout << "Crafting Table" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "|";
        for (int j = 0; j < 3; j++) {
            cout << T[i][j];
            if (j != 3) {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }
}
