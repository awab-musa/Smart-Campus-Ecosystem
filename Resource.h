#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>
#include "IComparable.h"

using namespace std;

class Resource : public IComparable
{
protected:
    string resourceID;
    string name;
    double price;
    int stock;

public:
    Resource();
    Resource(const string &id, const string &name, double price, int stock);
    virtual ~Resource() = default;

    string getResourceID() const;
    string getName() const;
    double getPrice() const;
    int getStock() const;

    void setPrice(double p);
    void setStock(int s);

    void restock(int qty);
    void purchase(int qty);

    virtual void displayInfo() const = 0;
    virtual string getCategory() const = 0;

    bool compareCost(const Resource *other) const override;

    bool operator>(const Resource &other) const;
    bool operator<(const Resource &other) const;

    friend ostream &operator<<(ostream &os, const Resource &r);

    virtual string serialize() const = 0;
    virtual string getTypeTag() const = 0;
};

template <typename Container>
Resource *findById(Container &container, const string &id)
{
    for (auto &item : container)
    {
        if (item->getResourceID() == id)
            return item;
    }
    return nullptr;
}

#endif