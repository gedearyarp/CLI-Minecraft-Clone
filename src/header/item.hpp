#ifndef __ITEM_H
#define __ITEM_H
#include <string>
#define MAX_NONTOOL 64

using namespace std;

class item
{
protected:
    int id;
    string name;
    string type;     // LOG, PLANK, STONE, -
    string category; // TOOL & NONTOOL

public:
    item();
    item(int id, string name, string type, string category);
    item(string name);
    int get_id();
    string get_name();
    virtual void itemInfo() const;
};

class tool : virtual public item
{
private:
    int durability;

public:
    tool();
    tool(int id, string name, int durability);
    tool(string name);
    void use();
    void itemInfo() const;
};

class nontool : virtual public item
{
private:
    int quantity;

public:
    nontool();
    nontool(int id, string name, string type, int quantity);
    void itemInfo() const;
};

#endif