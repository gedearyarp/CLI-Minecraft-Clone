#include <fstream>
#include <iostream>
#include <string>

#include "../header/itemConfig.hpp"

ItemConfig::ItemConfig(string configPath, string fileName)
{
    vector<Item> itemConfigs;
    // string configPath = "./config";
    // string itemConfigPath = configPath + "/item.txt";
    string itemConfigPath = configPath + "/" + fileName;

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
    this->configs = itemConfigs;
}

vector<Item> ItemConfig::getItemConfig() const
{
    return this->configs;
}

int ItemConfig::findIdByName(string nameItem) const
{
    for(int i=0; i<this->configs.size(); i++){
        if(this->configs[i].getName() == nameItem) return this->configs[i].getId();
    }
    return -1;
}

string ItemConfig::findTypeByName(string nameItem) const
{
    for(int i=0; i<this->configs.size(); i++){
        if(this->configs[i].getName() == nameItem) return this->configs[i].getType();
    }
    return "-";
}

string ItemConfig::findCategoryByName(string nameItem) const
{
    for(int i=0; i<this->configs.size(); i++){
        if(this->configs[i].getName() == nameItem) return this->configs[i].getCategory();
    }
    return "-";
}