// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "./src/implementation/itemConfig.cpp"
#include "./src/implementation/item.cpp"

using namespace std;
int main()
{
  string configPath = "./config";
  string fileName = "item.txt";

  // read item from config file
  ItemConfig readItemConfig = ItemConfig(configPath, fileName);

  // for (int i = 0; i < readItemConfig.getItemConfig().size(); i++){
  //   readItemConfig.getItemConfig()[i].itemInfo();
  //   cout << endl;
  // }

  // read recipes
  readItemConfig.displayItems();
}