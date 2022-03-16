#ifndef __ITEM_H
#define __ITEM_H

#include <string>
#include <vector>

using namespace std;
#define MAX_NONTOOL 64

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
    string get_name() const;
    string get_type() const;
    string get_category() const;
    string get_name();

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
    
    int getDurability() const;
    void setDurability(int durability);
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
    NonTool(string name, int quantity);

    bool isFull() const;

    int getQuantity() const;
    void setQuantity(int qty);

    void itemInfo() const;
};
#endif