#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <iostream>
#include "OrderItem.h"
#include "DeliveryMethod.h"
using namespace std;

class User;

class Order
{
private:
    string orderID;
    vector<OrderItem> items;
    const User *user;
    DeliveryMethod *delivery;
    string orderDate;

    static int orderCounter;
    static string generateOrderID();

public:
    Order();
    Order(const User *user, DeliveryMethod *delivery);
    ~Order();

    void addItem(Resource *resource, int quantity);
    void removeItem(const string &resourceID);
    bool hasItems() const;
    int itemCount() const;

    double calcSubtotal() const;
    double calcDiscount() const;
    double calcDeliveryCost() const;
    double calcTotal() const;

    string getOrderID() const;
    const vector<OrderItem> &getItems() const;
    const User *getUser() const;
    DeliveryMethod *getDelivery() const;
    string getOrderDate() const;

    void displaySummary() const;
    void displayReceipt() const;
    string serialize() const;

    friend ostream &operator<<(ostream &os, const Order &o);
};

#endif