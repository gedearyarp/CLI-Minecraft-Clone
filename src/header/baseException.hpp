#ifndef __BASE_EXCEPTION_HPP__
#define __BASE_EXCEPTION_HPP__

#include <iostream>
using namespace std;

class BaseException {
public:
    virtual void printMessage();
};
 
class IndexOutOfRangeException : public BaseException {
private:
    int idx;
public:
    IndexOutOfRangeException(int idx);
    void printMessage();
};

class InvalidQuantityException : public BaseException {
private:
    int qty;
public:
    InvalidQuantityException(int qty);
    void printMessage();
};

class EmptySlotException : public BaseException {
private:
    int row;
    int col;
public:
    EmptySlotException(int row, int col);
    void printMessage();
};

class DiscardQuantityException : public BaseException {
private:
    int slotQty;
    int discardQty;
public:
    DiscardQuantityException(int slotQty, int discardQty);
    void printMessage();
};

class InvalidInventoryTextException : public BaseException {
private:
    string str;
public:
    InvalidInventoryTextException(string str);
    void printMessage();
};

class OpenFileErrorException : public BaseException {
private:
    string fileName;
public:
    OpenFileErrorException(string fileName);
    void printMessage();
};

class InvalidNameException : public BaseException {
private:
    string itemName;
public:
    InvalidNameException(string itemName);
    void printMessage();
};

class InvalidIDException : public BaseException {
private:
    int id;
public:
    InvalidIDException(int id);
    void printMessage();
};

class InvalidDestinationSlot : public BaseException {
private:
    int id;
public:
    InvalidDestinationSlot(int id);
    void printMessage();
};

#endif