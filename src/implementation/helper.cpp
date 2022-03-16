#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "../header/helper.hpp"
#include "../header/item.hpp"

vector<Item> readConfigPath(){
    vector<Item> itemConfigs;
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
        itemConfigs.push_back(Item(stoi(id),name,type,category));
    }
    return itemConfigs;
}

string findCategoryByName(string nameItem){
    vector<Item> itemConfigs = readConfigPath();

    for(int i=0; i<itemConfigs.size(); i++){
        if(itemConfigs[i].name == nameItem) return itemConfigs[i].category;
    }
}