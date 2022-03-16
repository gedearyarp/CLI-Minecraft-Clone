#include "../header/item.hpp"
#include <iostream>
using namespace std;

item::item()
{
    this->id = 0;
    this->name = "-";
    this->type = "type";
    this->category = "-";
}
item::item(int id, string name, string type, string category)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->category = category;
}
item::item(string name)
{
    // nyari tau id dan tipe dari config file
}

int item::get_id()
{
    return this->id;
}

string item::get_name()
{
    return this->name;
}

tool::tool() : item(0, "name", "-", "TOOL")
{
    this->durability = 10;
}
tool::tool(int id, string name, int durability) : item(id, name, "-", "TOOL")
{
    this->durability = durability;
}
tool::tool(string name) : item(name)
{
    this->durability = 10;
}
void tool::use()
{
    this->durability--;
    if (this->durability <= 0)
    {
        // Ilang dari inventory
    }
}

void tool::itemInfo() const
{
    cout << "ID :" << this->id << endl;
    cout << "Name :" << this->name << endl;
    cout << "Type :" << this->type << endl;
    cout << "Durability :" << this->durability << endl;
}

nontool::nontool() : item(0, "-", "-", "-")
{
    this->quantity = 0;
}

nontool::nontool(int id, string name, string type, int quantity) : item(id, name, type, "NONTOOL")
{
    this->quantity = quantity;
}

void nontool::itemInfo() const
{
    cout << "ID :" << this->id << endl;
    cout << "Name :" << this->name << endl;
    cout << "Type :" << this->type << endl;
    cout << "Quantity :" << this->quantity << endl;
}