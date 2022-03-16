#include "../header/item.hpp"
#include <iostream>

using namespace std;

Item::Item()
{
    this->id = 0;
    this->name = "-";
    this->type = "type";
    this->category = "-";
}
Item::Item(int id, string name, string type, string category)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->category = category;
}
Item::Item(string name)
{
    // nyari tau id dan tipe dari config file
}

int Item::get_id()
{
    return this->id;
}

string Item::get_name()
{
    return this->name;
}

string Item::get_category()
{
    return this->category;
}

Tool::Tool() : Item(0, "name", "-", "TOOL")
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
    cout << "ID :" << this->id << endl;
    cout << "Name :" << this->name << endl;
    cout << "Type :" << this->type << endl;
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

void NonTool::itemInfo() const
{
    cout << "ID :" << this->id << endl;
    cout << "Name :" << this->name << endl;
    cout << "Type :" << this->type << endl;
    cout << "Quantity :" << this->quantity << endl;
}