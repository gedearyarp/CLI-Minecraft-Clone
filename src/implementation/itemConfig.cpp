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
            if (line[i] != ' ' && line[i] != '\n' && line[i] != '\r')
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
        if (type == "-")
        {
            type = name;
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
    throw new InvalidNameException(nameItem); // TODO THROW invalid item name
}

string ItemConfig::findTypeByName(string nameItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getName() == nameItem)
            return this->configs[i].getType();
    }
    throw new InvalidNameException(nameItem); // TODO THROW invalid item name
}

string ItemConfig::findCategoryByName(string nameItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getName() == nameItem)
            return this->configs[i].getCategory();
    }
    throw new InvalidNameException(nameItem);
     // TODO THROW invalid item name
}

string ItemConfig::findNameById(int idItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getId() == idItem)
            return this->configs[i].getName();
    }
    throw new InvalidIDException(idItem);// TODO THROW invalid item id
}

string ItemConfig::findTypeById(int idItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getId() == idItem)
            return this->configs[i].getType();
    }
    throw new InvalidIDException(idItem); // TODO THROW invalid item id
}

string ItemConfig::findCategoryById(int idItem) const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getId() == idItem)
            return this->configs[i].getCategory();
    }
    throw new InvalidIDException(idItem); // TODO THROW invalid item id
}

void ItemConfig::displayItems() const
{
    for (int i = 0; i < this->configs.size(); i++)
    {
        this->configs.at(i).itemInfo();
    }
}

bool ItemConfig::isType(string name)
{
    int i = 0;
    bool found = false;
    while (!found && i < this->configs.size())
    {
        if (this->configs[i].getType() == name)
        {
            found = true;
        }
        i++;
    }
    return found;
}

vector<string> ItemConfig::listOfItemWithType(string itemType)
{
    vector<string> items;
    for (int i = 0; i < this->configs.size(); i++)
    {
        if (this->configs[i].getType() == itemType)
        {
            items.push_back(this->configs[i].getName());
        }
    }
    return items;
}