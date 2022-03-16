// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "./src/implementation/item.cpp"

using namespace std;
int main() {
  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  // read item from config file
  ifstream itemConfigFile(itemConfigPath);
  for (string line; getline(itemConfigFile, line);) {
    int spaces = 0;
    string id = ""; string name = ""; string type = ""; string category = "";
    for (int i = 0; i < line.size(); i++){
      if (line[i] != ' '){
          if (spaces == 0) id += line[i];
          else if (spaces == 1) name += line[i];
          else if (spaces == 2) type += line[i];
          else if (spaces == 3) category += line[i];
      }
      else {
        spaces += 1;
      }
    }
    itemConfigs.push_back(*new Item(stoi(id),name,type,category));
  }
  // for (int i = 0; i < itemConfigs.size(); i++){
  //   itemConfigs[i].itemInfo();
  //   cout << endl;
  // }

  // read recipes
  for (const auto &entry :
       filesystem::directory_iterator(configPath + "/recipe")) {
    cout << entry.path() << endl;
    // read from file and do something
  }

  // sample interaction
  string command;
  while (cin >> command) {
    if (command == "EXPORT") {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);

      // hardcode for first test case
      outputFile << "21:10" << endl;
      outputFile << "6:1" << endl;
      for (int i = 2; i < 27; i++) {
        outputFile << "0:0" << endl;
      }

      cout << "Exported" << endl;
    } else if (command == "CRAFT") {
      cout << "TODO" << endl;
    } else if (command == "GIVE") {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      cout << "TODO" << endl;
    } else if (command == "MOVE") {
      string slotSrc;
      int slotQty;
      string slotDest;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty >> slotDest;
      cout << "TODO" << endl;
    } else {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
