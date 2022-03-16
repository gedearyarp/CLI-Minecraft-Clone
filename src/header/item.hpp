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

    int getId();
    string getName() const;
    string getType() const;
    string getCategory() const;

    bool isNothing() const;

    virtual int getQuantity();
    virtual int getDurability();
    virtual void setQuantity(int qty);
    virtual void setDurability(int durability);
    virtual bool isEmpty() const;
    virtual bool isFull() const;
    // enam fungsi diatas cuman buat ga error kalo dipanggil ke data (Item& X = NonTool) atau (Item& Y = Tool)

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
    bool isEmpty() const;

    int getQuantity() const;
    void setQuantity(int qty);

    void itemInfo() const;
};
#endif