#include "../header/item.hpp"

item::item(){
    this->id=0;
    this->name="name";
    this->type="type";
}
item::item(int id, string name, string type){
    this->id=id;
    this->name=name;
    this->type=type;
}
item::item(string name){
    // nyari tau id dan tipe dari config file
}


tool::tool() : item(0,"name","-"){
    this->durability=10;
}
tool::tool(int id, string name, int durability) : item(id,name,"-"){
    this->durability=durability;
}
tool::tool(string name) : item(name){
    this->durability=10;
}
void tool::use(){
    this->durability--;
    if (this->durability <= 0){
        // Ilang dari inventory
    }
}

