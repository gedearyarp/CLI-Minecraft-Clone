#ifndef ITEMCONFIG_HPP
#define ITEMCONFIG_HPP

#include "item.hpp"
#include "baseException.hpp"

class ItemConfig
{
private:
    vector<Item> configs;

public:
    ItemConfig(string configPath, string fileName);

    vector<Item> getItemConfig() const;

    int findIdByName(string nameItem) const;
    string findTypeByName(string nameItem) const;
    string findCategoryByName(string nameItem) const;
    string findNameById(int idItem) const;
    string findTypeById(int idItem) const;
    string findCategoryById(int idItem) const;
    void displayItems() const;
    bool isType(string name); // buat ngecek apakah name merupakan nama type yang bakal punya item turunan
    vector<string> listOfItemWithType(string itemType); // balikin semua item dengan type itemType
};

#endif