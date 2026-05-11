#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class Order;

class User
{
protected:
    string name;
    string campusID;

public:
    User();
    User(const string &name, const string &campusID);
    virtual ~User() = default;

    string getName() const;
    string getCampusID() const;
    void setName(const string &n);
    void setCampusID(const string &id);

    virtual double getDiscount() const = 0;
    virtual string getRole() const = 0;
    virtual string getTypeTag() const = 0;
    virtual void displayProfile() const = 0;
    virtual string serialize() const = 0;

    void placeOrder(Order &order) const;
    string getProfile() const;

    friend ostream &operator<<(ostream &os, const User &u);
};

#endif