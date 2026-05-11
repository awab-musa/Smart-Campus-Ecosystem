#ifndef DELIVERY_METHOD_H
#define DELIVERY_METHOD_H

#include <string>
#include <iostream>
using namespace std;

class DeliveryMethod
{
protected:
    string methodName;

public:
    DeliveryMethod();
    explicit DeliveryMethod(const string &name);
    virtual ~DeliveryMethod() = default;

    string getMethodName() const;

    virtual double getCost() const = 0;
    virtual string getDescription() const = 0;
    virtual string getTypeTag() const = 0;

    friend ostream &operator<<(ostream &os, const DeliveryMethod &d);
};

#endif