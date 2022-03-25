#include <bits/stdc++.h> 
#include "../../src/implementation/baseException.cpp"
#include "../../src/implementation/itemConfig.cpp" 
#include "../../src/implementation/item.cpp"  

using namespace std;

int main() {
	srand((unsigned)time(0));

	string configPath = "..";
    string fileName = "item.txt";
    ItemConfig readItemConfig = ItemConfig(configPath, fileName);

    ofstream inv;
    inv.open("inventory.txt");

	for(int i=0; i<27; i++){
		int cur = rand();
		if(cur%4 == 0) inv << "0:0" << '\n';
		else {
			int idItem = rand()%38 + 1;
			if(readItemConfig.findCategoryById(idItem) == "TOOL"){
				inv << idItem << ":" << (rand() % 10 + 1) << '\n';
			} else {
				inv << idItem << ":" << (rand() % 64 + 1) << '\n';
			}
		}
	}

    inv.close();
}