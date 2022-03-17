#ifndef ITEMCONFIG_HPP
#define ITEMCONFIG_HPP

#include "../header/item.hpp"

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
};


#endif