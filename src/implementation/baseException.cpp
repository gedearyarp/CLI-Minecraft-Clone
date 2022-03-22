#include <iostream>
#include "../header/baseException.hpp"

using namespace std;

void BaseException::printMessage() {
    cout << "Error Occured." << '\n';
}

IndexOutOfRangeException::IndexOutOfRangeException(int idx){
    this->idx = idx;
}

void IndexOutOfRangeException::printMessage(){
    cout << "Index " << this->idx << " is out of range." << '\n';
}

InvalidQuantityException::InvalidQuantityException(int qty){
    this->qty = qty;
}

void InvalidQuantityException::printMessage(){
    cout << "Quantity" << this->qty << " is invalid." << '\n';
}

EmptySlotException::EmptySlotException(int row, int col){
    this->row = row;
    this->col = col;
}

void EmptySlotException::printMessage(){
    int slotIdx = 9*row + col;
    cout << "Slot with id I" << slotIdx << "is Empty." << '\n'; 
}

DiscardQuantityException::DiscardQuantityException(int slotQty, int discardQty){
    this->slotQty = slotQty;
    this->discardQty = discardQty;
}

void DiscardQuantityException::printMessage(){
    cout << "The slot quantity (" << slotQty << ") is smaller than discard quantity (" << discardQty << ")." << '\n';
}

InvalidInventoryTextException::InvalidInventoryTextException(string str){
    this->str = str;
}

void InvalidInventoryTextException::printMessage(){
    cout << "Invalid format on this text -> \"" << str << "\"." << '\n';
}

OpenFileErrorException::OpenFileErrorException(string fileName){
    this->fileName = fileName;
}

void OpenFileErrorException::printMessage(){
    cout << "Error while opening \"" << fileName << "\"." << '\n';
}

InvalidNameException::InvalidNameException(string itemName)
{
    this->itemName = itemName;
}

void InvalidNameException::printMessage(){
    cout << itemName << "is not a valid item name" << endl;
}

InvalidIDException::InvalidIDException(int id)
{
    this->id = id;
}

void InvalidIDException::printMessage(){
    cout << id << "is not a valid item id" << endl;
}

InvalidDestinationSlot::InvalidDestinationSlot(int id)
{
    this->id = id;
}

void InvalidDestinationSlot::printMessage(){
    cout << id << "is not a valid destionation" << endl;
}