#include "../header/item.hpp"
#include <iostream>

using namespace std;

vector<Item> itemConfigs;

Item::Item()
{
    this->id = -1;
    this->name = "-";
    this->type = "type";
    this->category = "-";
} // ini kenapa ga declare = NULL aja terus id nya -1 (igede)

Item::Item(int id, string name, string type, string category)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->category = category;
}

Item::Item(string name)
{
    bool found = false;
    int i = 0;
    while (!found && i < itemConfigs.size()){
        if (itemConfigs[i].name == name) found = true;
        else i++;
    }
    this->id = itemConfigs[i].id;
    this->name = itemConfigs[i].name;
    this->type = itemConfigs[i].type;
    this->category = itemConfigs[i].category;
}

int Item::getId()
{
    return this->id;
}

string Item::getName() const
{
    return this->name;
}

string Item::getType() const
{
    return this->type;
}

string Item::getCategory() const
{
    return this->category;
}

void Item::itemInfo() const
{
    cout << "ID :" << this->id << endl;
    cout << "Name :" << this->name << endl;
    cout << "Type :" << this->type << endl;
}

Tool::Tool() : Item(0, "-", "-", "TOOL")
{
    this->durability = 10;
}

Tool::Tool(int id, string name, int durability) : Item(id, name, "-", "TOOL")
{
    this->durability = durability;
}

Tool::Tool(string name) : Item(name)
{
    this->durability = 10;
}

int Tool::getDurability() const{
    return this->durability;
}

void Tool::setDurability(int durability) 
{
    this->durability = durability;
}

void Tool::use()
{
    this->durability--;
    if (this->durability <= 0)
    {
        // Ilang dari inventory
    }
}
void Tool::itemInfo() const
{
    Item::itemInfo();
    cout << "Durability :" << this->durability << endl;
}

NonTool::NonTool() : Item(0, "-", "-", "-")
{
    this->quantity = 0;
}

NonTool::NonTool(int id, string name, string type, int quantity) : Item(id, name, type, "NONTOOL")
{
    this->quantity = quantity;
}

NonTool::NonTool(string name, int quantity) : Item(name)
{
    this->quantity = quantity;
}

bool NonTool::isFull() const{
    return this->quantity >= 64;
}

int NonTool::getQuantity() const{
    return this->quantity;
}

void NonTool::setQuantity(int qty) {
    this->quantity = qty;
}

void NonTool::itemInfo() const
{
    Item::itemInfo();
    cout << "Quantity :" << this->quantity << endl;
}