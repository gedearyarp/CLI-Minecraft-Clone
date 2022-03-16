#ifndef __ITEM_H
#define __ITEM_H
#include <string>
#define MAX_NONTOOL 64

using namespace std;

class Item
{
protected:
    int id;
    string name;
    string type;     // LOG, PLANK, STONE, -
    string category; // TOOL & NONTOOL

public:
    Item();
    Item(int id, string name, string type, string category);
    Item(string name);
    int get_id();
    string get_name();
    string get_category();
    virtual void itemInfo() const;
};

class Tool : virtual public Item
{
private:
    int durability;

public:
    Tool();
    Tool(int id, string name, int durability);
    Tool(string name);
    void use();
    void itemInfo() const;
};

class NonTool : virtual public Item
{
private:
    int quantity;

public:
    NonTool();
    NonTool(int id, string name, string type, int quantity);
    void itemInfo() const;
};

#endif