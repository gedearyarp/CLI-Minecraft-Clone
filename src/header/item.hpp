#ifndef __ITEM_H
#define __ITEM_H
#include <string>

using namespace std;

class item{
protected:
    int id;
    string name;
    string type;    //LOG, PLANK, STONE, - 
public:
    item();
    item(int id, string name, string type);
    item(string name);
};

class tool : virtual public item{
private:
    int durability;
public:
    tool();
    tool(int id, string name, int durability);
    tool(string name);
    void use();
};

// class nontool : virtual public item{
// private:
//     int quantity;
// public:
//     nontool();
//     nontool(int id, string name, int quanitity);
// };
#endif