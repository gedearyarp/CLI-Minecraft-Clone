#include <fstream>
#include <iostream>
#include <string>

#include "../header/itemConfig.hpp"

ItemConfig::ItemConfig(string configPath, string fileName)
{
    vector<Item> itemConfigs;
    string itemConfigPath = configPath + "/" + fileName;

    // read item from config file
    ifstream itemConfigFile(itemConfigPath);
    for (string line; getline(itemConfigFile, line);)
    {
        int spaces = 0;
        string id = "";
        string name = "";
        string type = "";
        string category = "";
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] != ' ')
            {
                if (spaces == 0)
                    id += line[i];
                else if (spaces == 1)
                    name += line[i];
                else if (spaces == 2)
                    type += line[i];
                else if (spaces == 3)
                    category += line[i];
            }
            else
            {
                spaces += 1;
            }
        }
        itemConfigs.push_back(Item(stoi(id), name, type, category));
    }
    this->configs = itemConfigs;
}

vector<Item> ItemConfig::getItemConfig() const
{
    return this->configs;
}

int ItemConfig::findIdByName(string nameItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getName() == nameItem)
            return this->configs[i].getId();
    }
    return -1; //TODO THROW invalid item name
}

string ItemConfig::findTypeByName(string nameItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getName() == nameItem)
            return this->configs[i].getType();
    }
    return "-"; //TODO THROW invalid item name
}

string ItemConfig::findCategoryByName(string nameItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getName() == nameItem)
            return this->configs[i].getCategory();
    }
    return "-"; //TODO THROW invalid item name
}

string ItemConfig::findNameById(int idItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getId() == idItem)
            return this->configs[i].getName();
    }
    return "-"; //TODO THROW invalid item id
}

string ItemConfig::findTypeById(int idItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getId() == idItem)
            return this->configs[i].getType();
    }
    return "-"; //TODO THROW invalid item id
}

string ItemConfig::findCategoryById(int idItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getId() == idItem)
            return this->configs[i].getCategory();
    }
    return "-"; //TODO THROW invalid item id
}

void ItemConfig::displayItems() const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        this->configs.at(i).itemInfo();
    }
}