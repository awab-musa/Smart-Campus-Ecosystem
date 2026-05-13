#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include <string>
#include <iostream>
#include "Resource.h"
using namespace std;

class OrderItem
{
private:
    Resource *resource;
    int quantity;

public:
    OrderItem();
    OrderItem(Resource *resource, int quantity);

    Resource *getResource() const;
    int getQuantity() const;
    void setQuantity(int q);

    double getLineTotal() const;
    void display() const;

    friend ostream &operator<<(ostream &os, const OrderItem &item);
};

#endif