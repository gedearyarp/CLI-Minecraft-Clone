#ifndef __ITEM_H
#define __ITEM_H

#include <string>
#include <vector>
#include <algorithm>

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
    Item(string name, vector<Item> config);

    int getId() const;
    string getName() const;
    string getType() const;
    string getCategory() const;

    bool isNothing() const;
    bool isType(string name); // buat ngecek apakah name merupakan nama type yang bakal punya item turunan
    bool isItemChildofParent(string itemName);

    vector<string> listOfItemWithType(string itemType); // balikin semua item dengan type itemType

    virtual int getQuantity() const;
    virtual int getDurability() const;
    virtual void setQuantity(int qty);
    virtual void setDurability(int durability);
    virtual bool isEmpty() const;
    virtual bool isFull() const;
    // enam fungsi diatas cuman buat ga error kalo dipanggil ke data (Item& X = NonTool) atau (Item& Y = Tool)
    // (JANGAN DIPAKAI KALO BUKAN SUBCLASS ITEM)

    virtual void itemInfo() const;
};

class Tool : virtual public Item
{
private:
    int durability;

public:
    Tool();
    Tool(int id, string name, int durability);
    Tool(string name, vector<Item> config);
    Tool(string name, int durability, vector<Item> config);

    int getDurability() const;
    void setDurability(int durability);
    int getQuantity() const; // bakal selalu return 1
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
    NonTool(string name, int quantity, vector<Item> config);

    bool isFull() const;
    bool isEmpty() const;

    int getQuantity() const;
    void setQuantity(int qty);

    void itemInfo() const;
};
#endif